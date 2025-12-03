#include "Clue3.h"

//enum for controlling the cutscene thing
enum Clue3Stage { STAGE_SHOW_BLUR, STAGE_FIND_KEY, STAGE_MINIGAME, STAGE_SHOW_CLEAR, STAGE_POST_MINIGAME, STAGE_SHOW_FINAL, STAGE_EXIT_PROMPT };

static Clue3Stage stage = STAGE_SHOW_BLUR; // starting with blur

Clue3::Clue3() : Scene({0.0f}, nullptr) {}
Clue3::Clue3(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Clue3::~Clue3() { shutdown(); }

void Clue3::initialise()
{
    textureBG = LoadTexture("assets/cutsceneoverlay.PNG");
    textureClue1 = LoadTexture("assets/clue3/clue3_1.PNG");
    textureClue2 = LoadTexture("assets/clue3/clue3_2.PNG");
    textureClue3 = LoadTexture("assets/clue3/clue3_3.PNG");
    textureClue4 = LoadTexture("assets/clue3/clue3_4.PNG");
    textureClue5 = LoadTexture("assets/clue3/clue3_5.PNG");
    textureClue6 = LoadTexture("assets/clue3/clue3_6.PNG");
    textureClue7 = LoadTexture("assets/clue3/clue3_7.PNG");
    textureClue8 = LoadTexture("assets/clue3/clue3_8.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    mGameState.nextSceneID = -1;

    // mGameState.bgm = LoadMusicStream("assets/void.mp3");
    // SetMusicVolume(mGameState.bgm, 0.50f);
    // PlayMusicStream(mGameState.bgm);

    mGameState.bg = new Entity(
        mOrigin,                                        // position
        { 990.0f, 720.0f },                             // size
        textureBG,                                      // texture file address
        NONE                                            // type
    );

    // ------------ CUTSCENE -------------
    mGameState.cutscene = new Entity(
        mOrigin,                                        // position
        { 990.0f, 720.0f },                             // size
        textureClue1,                                      // texture file address
        NONE                                            // type
    );
    mGameState.cutscene->setColliderDimensions({
        75.0f,
        150.0f
    });
    mGameState.cutscene->setColliderOffset({
        0.0f,
        75.0f
    });

    // ------------ DIALOGUE BOX -------------
    mGameState.dialoguebox = new Entity(
        { mOrigin.x, 600.0f },
        { 775.0f, 155.0f },
        textureDialogueBox,
        NONE
    );

    stage = STAGE_SHOW_BLUR; // starting with blur
    mGameState.dialogueActive = true;
    mGameState.dialogueStep = 0;
    mGameState.dialogueText = "Click and find the key";

    minigameActive = false;
    minigameTimer = 0.0f;
    fillAmount = 0.0f;
    tappedOnce = false;
    triesLeft = 3;
    autoSequenceRunning = false;
    autoSeqTimer = 0.0f;
    autoSeqIndex = 0;
    pulseTimer = 0.0f;

    showExitPrompt = false;
}

void Clue3::update(float deltaTime)
{
    if (stage == STAGE_MINIGAME){
        pulseTimer += deltaTime * pulseSpeed;
    }

    if (stage == STAGE_SHOW_BLUR && mGameState.dialogueActive){ // start dialogue
        if (IsKeyPressed(KEY_E)){ // close dialogue and start minigame
            mGameState.dialogueActive = false;
            stage = STAGE_FIND_KEY;
            mGameState.cutscene->setTexture(textureClue1);
            triesLeft = 3;
            return;
        }
    }

    if (stage == STAGE_FIND_KEY && !autoSequenceRunning){
        Vector2 mouse = GetMousePosition();
        Vector2 cutPos = mGameState.cutscene->getPosition();
        Vector2 offset = mGameState.cutscene->getColliderOffset();
        Vector2 center = { cutPos.x + offset.x, cutPos.y + offset.y };
        Vector2 dims = mGameState.cutscene->getColliderDimensions();
        float halfW = dims.x * 0.5f;
        float halfH = dims.y * 0.5f;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if ((fabs(mouse.x - center.x) <= halfW) && (fabs(mouse.y - center.y) <= halfH)){ // found the key
                autoSequenceRunning = true;
                autoSeqTimer = 0.0f;
                autoSeqIndex = 0;
                mGameState.cutscene->setTexture(textureClue2);
            }
            else{ // wrong click
                triesLeft--;
                if (triesLeft <= 0){ // fail bad end
                    mGameState.nextSceneID = 7;
                    return;
                }
                else{ // show text for worng move
                    mGameState.dialogueActive = true;
                    mGameState.dialogueStep = 0;
                    mGameState.dialogueText = "No... that's not it";
                    return;
                }
            }
        }
    }

    if (autoSequenceRunning){
        autoSeqTimer += deltaTime;
        if (autoSeqTimer >= autoSeqStep){
            autoSeqTimer = 0.0f;
            autoSeqIndex++;
            if (autoSeqIndex == 1){
                mGameState.cutscene->setTexture(textureClue3);
            }
            else if (autoSeqIndex == 2){
                mGameState.cutscene->setTexture(textureClue4);
            }
            else{ // done showing, now dialogue before minigame
                autoSequenceRunning = false;
                stage = STAGE_SHOW_CLEAR;
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "not again..";
                mGameState.dialogueStep = 0;
                return;
            }
        }
    }

    if (stage == STAGE_SHOW_CLEAR && mGameState.dialogueActive){
        if (IsKeyPressed(KEY_E)){ // start mini game
            mGameState.dialogueActive = false;
            stage = STAGE_MINIGAME;
            minigameActive = true;
            minigameTimer = 0.0f;
            fillAmount = 0.0f;
            tappedOnce = false;
            return;
        }
    }

    // mini game things
    if (stage == STAGE_MINIGAME && minigameActive){
        if (IsKeyPressed(KEY_P)){ // counting the P key taps
            fillAmount += fillPerTap;
            tappedOnce = true;
            if (fillAmount > fillTarget) fillAmount = fillTarget;
        }

        // drain over time
        fillAmount -= drainPerSecond * deltaTime;
        if (fillAmount < 0) fillAmount = 0;

        minigameTimer += deltaTime; // update timer

        if (fillAmount >= fillTarget - 0.5f){ // success continue
            minigameActive = false;
            stage = STAGE_POST_MINIGAME;
            Scene::setKeyFoundStatus(true);
            mGameState.cutscene->setTexture(textureClue5);
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "...";
            mGameState.dialogueStep = 0;
            return;
        }

        if ((minigameTimer >= minigameDuration) 
            || (tappedOnce && fillAmount == 0.0f)){ // fail go to bad end
            minigameActive = false;
            mGameState.nextSceneID = 7;
            return;
        }
    }

    if (stage == STAGE_POST_MINIGAME && mGameState.dialogueActive){
        if (IsKeyPressed(KEY_E)){
            mGameState.dialogueActive = false;
            stage = STAGE_SHOW_FINAL;
            mGameState.cutscene->setTexture(textureClue8); // final clue pic
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "I can do it this time";
            mGameState.dialogueStep = 0;
            return;
        }
    }

    if (stage == STAGE_SHOW_FINAL && mGameState.dialogueActive){
        if (IsKeyPressed(KEY_E)){
            mGameState.dialogueActive = false;
            mGameState.nextSceneID = 12; // go back to bedroom
            return;
        }
    }

}

void Clue3::render()
{
    ClearBackground(BLACK);

    // mGameState.cutscene->render();
    if (stage == STAGE_MINIGAME){
        float pulse = (sinf(pulseTimer) + 1.0f) * 0.5f; // 0..1
        float scaleMul = 1.0f + pulse * pulseAmount;

        Rectangle src = {
            0, 0,
            (float)mGameState.cutscene->getTexture().width,
            (float)mGameState.cutscene->getTexture().height
        };

        Rectangle dest = {
            mOrigin.x,
            mOrigin.y,
            990.0f * scaleMul,
            720.0f * scaleMul
        };

        Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };

        DrawTexturePro(
            mGameState.cutscene->getTexture(),
            src,
            dest,
            origin,
            0,
            WHITE
        );
    }
    else{
        // no shaking when clear
        mGameState.cutscene->render();
    }
    mGameState.bg->render(); // stays on top

    if (stage == STAGE_MINIGAME){ // rendering the minigame
        float barWidth = 600;
        float barHeight = 40;

        float x = (GetScreenWidth() - barWidth) / 2;
        float y = GetScreenHeight() - 130;

        // background bar black w/ white outline
        DrawRectangle(x, y, barWidth, barHeight, BLACK);
        DrawRectangleLines(x, y, barWidth, barHeight, WHITE);

        // fill bar just white
        float fillPercent = fillAmount / fillTarget;
        if (fillPercent > 1) fillPercent = 1;

        float fillWidth = barWidth * fillPercent;
        DrawRectangle(x, y, fillWidth, barHeight, WHITE);

        DrawText( // instruction
            "Press 'P' repeatedly!", 
            x + 10, 
            y - 30, 
            24, 
            WHITE
        );
    }

    if (mGameState.dialogueActive){ // dialogue and text
        if (mGameState.dialoguebox)
            mGameState.dialoguebox->render();

        int textX = mOrigin.x - 350;
        int textY = 600 - 50;

        DrawText(
            mGameState.dialogueText.c_str(),
            textX, textY,
            24,
            WHITE
        );

        const char* hint = "[E] to Interact";
        int fontSize = 20;
        int padding = 20;
        int textWidth = MeasureText(hint, fontSize);

        int drawX = GetScreenWidth() - textWidth - padding;
        int drawY = GetScreenHeight() - fontSize - padding;

        DrawText(
            hint, 
            drawX, 
            drawY, 
            fontSize, 
            WHITE
        );
    }

    if (stage == STAGE_EXIT_PROMPT){ // exit prompt
        const char* exitText = "[E] to return to the living room";
        int size = 28;
        int w = MeasureText(exitText, size);

        DrawText(
            exitText,
            (GetScreenWidth() - w) / 2,
            GetScreenHeight() - 140,
            size,
            WHITE
        );
    }

}

void Clue3::shutdown()
{
    delete mGameState.bg;
    UnloadTexture(textureClue1);
    UnloadTexture(textureClue2);
    UnloadTexture(textureClue3);
    UnloadTexture(textureClue4);
    UnloadTexture(textureClue5);
    UnloadTexture(textureClue6);
    UnloadTexture(textureClue7);
    UnloadTexture(textureClue8);
    UnloadTexture(textureDialogueBox);
}
