#include "Clue2.h"

//enum for controlling the cutscene thing
enum Clue2Stage { STAGE_SHOW_BLUR, STAGE_MINIGAME, STAGE_SHOW_CLEAR, STAGE_EXIT_PROMPT };

static Clue2Stage stage = STAGE_SHOW_BLUR; // starting with blur

Clue2::Clue2() : Scene({0.0f}, nullptr) {}
Clue2::Clue2(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Clue2::~Clue2() { shutdown(); }

void Clue2::initialise()
{
    textureBG = LoadTexture("assets/cutsceneoverlay.PNG");
    textureClue2Blur = LoadTexture("assets/clue2/clue2blur.PNG");
    textureClue2Clear = LoadTexture("assets/clue2/clue2clear.PNG");
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
        textureClue2Blur,                                      // texture file address
        NONE                                            // type
    );

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
    mGameState.dialogueText = "agh no.. it's happening again";

    minigameActive = true;
    minigameTimer = 0.0f;
    fillAmount = 0.0f;
    tappedOnce = false;

    showExitPrompt = false;
}

void Clue2::update(float deltaTime)
{
    if (stage == STAGE_SHOW_BLUR && mGameState.dialogueActive){ // start dialogue
        if (IsKeyPressed(KEY_E)){ // close dialogue and start minigame
            mGameState.dialogueActive = false;
            stage = STAGE_MINIGAME;
            minigameActive = true;
            minigameTimer = 0.0f;
            fillAmount = 0.0f;
            // tapCount = 0;
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
        // bool success = (fillAmount >= fillTarget) || (tapCount >= maxTapsForAutoWin);

        if (fillAmount >= fillTarget - 0.5f){ // show the clear image
            minigameActive = false;
            mGameState.cutscene->setTexture(textureClue2Clear);
            stage = STAGE_SHOW_CLEAR;
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "No, I'm okay, this is okay";
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

    // showing the clear clue
    if (stage == STAGE_SHOW_CLEAR && mGameState.dialogueActive){
        if (IsKeyPressed(KEY_E)){ // hide dialogue and then show exit prompt
            mGameState.dialogueActive = false;
            stage = STAGE_EXIT_PROMPT;
            showExitPrompt = true;
            return;
        }
    }

    if (stage == STAGE_EXIT_PROMPT && showExitPrompt){ // leaving the clue
        if (IsKeyPressed(KEY_E)){ // go to her room
            mGameState.nextSceneID = 9;
            return;
        }
    }

}

void Clue2::render()
{
    ClearBackground(BLACK);

    mGameState.cutscene->render();
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

void Clue2::shutdown()
{
    delete mGameState.bg;
    UnloadTexture(textureClue2Blur);
    UnloadTexture(textureClue2Clear);
    UnloadTexture(textureDialogueBox);
}
