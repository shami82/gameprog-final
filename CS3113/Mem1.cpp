#include "Mem1.h"

Mem1::Mem1() : Scene({0.0f}, nullptr) {}
Mem1::Mem1(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Mem1::~Mem1() { shutdown(); }

void Mem1::initialise()
{
    textureBG = LoadTexture("assets/cutsceneoverlay.PNG");
    textureMem1 = LoadTexture("assets/mem1/mem1_1.PNG");
    textureMem2 = LoadTexture("assets/mem1/mem1_2.PNG");
    textureMem3 = LoadTexture("assets/mem1/mem1_3.PNG");
    textureMem4 = LoadTexture("assets/mem1/mem1_4.PNG");
    textureMem5 = LoadTexture("assets/mem1/mem1_5.PNG");
    textureMem6 = LoadTexture("assets/mem1/mem1_6.PNG");
    textureMem7 = LoadTexture("assets/mem1/mem1_7.PNG");
    textureMem8 = LoadTexture("assets/mem1/mem1_8.PNG");
    textureMem9 = LoadTexture("assets/mem1/mem1_9.PNG");
    textureMem10 = LoadTexture("assets/mem1/mem1_10.PNG");
    textureMem11 = LoadTexture("assets/mem1/mem1_11.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    mGameState.nextSceneID = -1;

    // confirm puzzle 1 is complete
    Scene::setPuz1Status(true);

    mGameState.bgm = LoadMusicStream("assets/audio/memory.mp3");
    SetMusicVolume(mGameState.bgm, 0.70f);
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
    flash9Shown = false;

    mGameState.dialogueActive = true;
    mGameState.dialogueStep = 0;
    mGameState.dialogueText = "Ah";

}

void Mem1::update(float deltaTime)
{
    if (!flashing) UpdateMusicStream(mGameState.bgm);

    if (flashing){
        flashTimer += deltaTime;

        if (mGameState.dialogueStep == 8 && !flash9Shown){ // case 8 where we flash 9
            if (flashTimer >= 0.5f){ // rly quick
                flash9Shown = true;
                flashTimer = 0.0f;
                mGameState.dialogueStep = 9;
                mGameState.cutscene->setTexture(textureMem9);
                mGameState.dialogueText = "";
            }
            return;
        }

        if (mGameState.dialogueStep == 9){
            if (flashTimer >= 1.0f){
                flashTimer = 0.0f;

                mGameState.dialogueStep = 10;
                mGameState.cutscene->setTexture(textureMem10);
                mGameState.dialogueText = "";

                flashing = false; // allow E again
            }
            return;
        }
        return;
    }

    if (IsKeyPressed(KEY_E)){ // regular E skipping 
        mGameState.dialogueStep++;

        switch (mGameState.dialogueStep){
            case 1:
                mGameState.cutscene->setTexture(textureMem2);
                mGameState.dialogueText = "";
                break;

            case 2:
                mGameState.cutscene->setTexture(textureMem3);
                mGameState.dialogueText = "I haven't seen this in..";
                break;

            case 3:
                mGameState.cutscene->setTexture(textureMem4);
                mGameState.dialogueText = "..a long time";
                break;

            case 4:
                mGameState.cutscene->setTexture(textureMem5);
                mGameState.dialogueText = "Awww";
                break;

            case 5:
                mGameState.cutscene->setTexture(textureMem6);
                mGameState.dialogueText = "she really does like it";
                break;

            case 6:
                mGameState.cutscene->setTexture(textureMem7);
                mGameState.dialogueText = "Mhm, I told you she would sweetheart";
                break;

            case 7: // flashing from 8-10
                mGameState.cutscene->setTexture(textureMem8);
                flashing = true;
                flashTimer = 0.0f;
                flash9Shown = false;
                mGameState.dialogueStep = 8;
                StopMusicStream(mGameState.bgm);
                PlaySound(mGameState.ringing);
                break;

            case 11: // after flashing now 11
                mGameState.cutscene->setTexture(textureMem11);
                mGameState.dialogueText = "...she really did like it til the end";
                break;

            case 12:
                mGameState.nextSceneID = 3; // go back to attic
                break;
        }
    }
}

void Mem1::render()
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

void Mem1::shutdown()
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
    UnloadTexture(textureDialogueBox);
    UnloadMusicStream(mGameState.bgm);
    UnloadSound(mGameState.ringing);
}
