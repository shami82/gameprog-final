#include "Mem2.h"

Mem2::Mem2() : Scene({0.0f}, nullptr) {}
Mem2::Mem2(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Mem2::~Mem2() { shutdown(); }

void Mem2::initialise()
{
    textureBG = LoadTexture("assets/cutsceneoverlay.PNG");
    textureMem1 = LoadTexture("assets/mem2/mem2_1.PNG");
    textureMem2 = LoadTexture("assets/mem2/mem2_2.PNG");
    textureMem3 = LoadTexture("assets/mem2/mem2_3.PNG");
    textureMem4 = LoadTexture("assets/mem2/mem2_4.PNG");
    textureMem5 = LoadTexture("assets/mem2/mem2_5.PNG");
    textureMem6 = LoadTexture("assets/mem2/mem2_6.PNG");
    textureMem7 = LoadTexture("assets/mem2/mem2_7.PNG");
    textureMem8 = LoadTexture("assets/mem2/mem2_8.PNG");
    textureMem9 = LoadTexture("assets/mem2/mem2_9.PNG");
    textureMem10 = LoadTexture("assets/mem2/mem2_10.PNG");
    textureMem11 = LoadTexture("assets/mem2/mem2_11.PNG");
    textureMem12 = LoadTexture("assets/mem2/mem2_12.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    mGameState.nextSceneID = -1;

    // confirm puzzle 2 is complete
    Scene::setPuz2Status(true);

    mGameState.bgm = LoadMusicStream("assets/audio/memory.mp3");
    SetMusicVolume(mGameState.bgm, 0.85f);
    mGameState.ringing = LoadSound("assets/audio/ringing.mp3");
    SetSoundVolume(mGameState.ringing, 1.0f);
    PlayMusicStream(mGameState.bgm);

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
        textureMem1,                                      // texture file address
        NONE                                            // type
    );

    // ------------ DIALOGUE BOX -------------
    mGameState.dialoguebox = new Entity(
        { mOrigin.x, 600.0f },
        { 775.0f, 155.0f },
        textureDialogueBox,
        NONE
    );

    flashing = false;
    flashTimer = 0.0f;
    flash10Shown = false;

    mGameState.dialogueActive = true;
    mGameState.dialogueStep = 0;
    mGameState.dialogueText = "Ah...";

}

void Mem2::update(float deltaTime)
{
    if (!flashing) UpdateMusicStream(mGameState.bgm);

    if (flashing){
        flashTimer += deltaTime;

        if (mGameState.dialogueStep == 9 && !flash10Shown){ // case 9 where we flash 10
            if (flashTimer >= 0.5f){ 
                flash10Shown = true;
                flashTimer = 0.0f;

                mGameState.dialogueStep = 10;
                mGameState.cutscene->setTexture(textureMem10);
                mGameState.dialogueText = "";
            }
            return;
        }

        if (mGameState.dialogueStep == 10){
            if (flashTimer >= 1.0f){
                flashTimer = 0.0f;
                mGameState.dialogueStep = 11;
                mGameState.cutscene->setTexture(textureMem11);
                mGameState.dialogueText = "";

                flashing = false; // allow E again
            }
            return;
        }
        return;
    }

    if (IsKeyPressed(KEY_E)){ // regular E skipping 
        mGameState.dialogueStep++;

        switch (mGameState.dialogueStep) {
            case 1:
                mGameState.cutscene->setTexture(textureMem2);
                mGameState.dialogueText = "";
                break;

            case 2:
                mGameState.cutscene->setTexture(textureMem3);
                mGameState.dialogueText = "";
                break;

            case 3:
                mGameState.cutscene->setTexture(textureMem4);
                mGameState.dialogueText = "I haven't seen this since..";
                break;

            case 4:
                mGameState.cutscene->setTexture(textureMem5);
                mGameState.dialogueText = "Ah I'm so sorry again";
                break;

            case 5:
                mGameState.cutscene->setTexture(textureMem6);
                mGameState.dialogueText = "Haha no sweetheart, it's really alright";
                break;

            case 6:
                mGameState.cutscene->setTexture(textureMem7);
                mGameState.dialogueText = "So much for ending our anniversary perfectly";
                break;

            case 7:
                mGameState.cutscene->setTexture(textureMem8);
                mGameState.dialogueText = "Hey, a lil spill never hurt anyone";
                break;

            case 8:
                mGameState.cutscene->setTexture(textureMem9);
                mGameState.dialogueText = "let me get these tissues-";
                break;

            case 9:
                mGameState.cutscene->setTexture(textureMem10);
                flashing = true;
                flash10Shown = false;
                flashTimer = 0.0f;
                mGameState.dialogueStep = 10;
                StopMusicStream(mGameState.bgm);
                PlaySound(mGameState.ringing);
                break;

            case 12:
                mGameState.cutscene->setTexture(textureMem12);
                mGameState.dialogueText = "...I miss you";
                break;

            case 13:
                mGameState.nextSceneID = 3; // go back to attic
                break;
        }
    }
}

void Mem2::render()
{
    ClearBackground(BLACK);

    mGameState.cutscene->render();
    mGameState.bg->render(); // stays on top

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

        if (!flashing){
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
    }

}

void Mem2::shutdown()
{
    delete mGameState.bg;
    UnloadTexture(textureMem1);
    UnloadTexture(textureMem2);
    UnloadTexture(textureMem3);
    UnloadTexture(textureMem4);
    UnloadTexture(textureMem5);
    UnloadTexture(textureMem6);
    UnloadTexture(textureMem7);
    UnloadTexture(textureMem8);
    UnloadTexture(textureMem9);
    UnloadTexture(textureMem10);
    UnloadTexture(textureMem11);
    UnloadTexture(textureMem12);
    UnloadTexture(textureDialogueBox);

    UnloadMusicStream(mGameState.bgm);
    UnloadSound(mGameState.ringing);
}
