#include "End.h"

End::End() : Scene({0.0f}, nullptr) {}
End::End(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
End::~End() { shutdown(); }

void End::initialise()
{
    textureBG = LoadTexture("assets/cutsceneoverlay.PNG");
    textureEnd1 = LoadTexture("assets/end/end1.PNG");
    textureEnd2 = LoadTexture("assets/end/end2.PNG");
    textureEnd3 = LoadTexture("assets/end/end3.PNG");
    textureEnd4 = LoadTexture("assets/end/end4.PNG");
    textureEnd5 = LoadTexture("assets/end/end5.PNG");
    textureEnd6 = LoadTexture("assets/end/end6.PNG");
    textureEnd7 = LoadTexture("assets/end/end7.PNG");
    textureEnd8 = LoadTexture("assets/end/end8.PNG");
    textureEnd9 = LoadTexture("assets/end/end9.PNG");
    textureEnd10 = LoadTexture("assets/end/end10.PNG");
    textureEnd11 = LoadTexture("assets/end/end11.PNG");
    textureEnd12 = LoadTexture("assets/end/end12.PNG");
    textureEnd13 = LoadTexture("assets/end/end13.PNG");
    textureEnd14 = LoadTexture("assets/end/end14.PNG");
    textureEnd15 = LoadTexture("assets/end/end15.PNG");
    textureEnd16 = LoadTexture("assets/end/end16.PNG");
    textureEnd17 = LoadTexture("assets/end/end17.PNG");
    textureEnd18 = LoadTexture("assets/end/end18.PNG");
    textureEnd19 = LoadTexture("assets/end/end19.PNG");
    textureEnd20 = LoadTexture("assets/end/end20.PNG");
    textureEnd21 = LoadTexture("assets/end/end21.PNG");
    textureEnd22 = LoadTexture("assets/end/end22.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    mGameState.nextSceneID = -1;

    mGameState.bgm = LoadMusicStream("assets/audio/memory.mp3");
    SetMusicVolume(mGameState.bgm, 0.85f);
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
        textureEnd1,                                      // texture file address
        NONE                                            // type
    );

    // ------------ DIALOGUE BOX -------------
    mGameState.dialoguebox = new Entity(
        { mOrigin.x, 600.0f },
        { 775.0f, 155.0f },
        textureDialogueBox,
        NONE
    );

    mGameState.dialogueActive = true;
    mGameState.dialogueStep = 0;
    mGameState.dialogueText = "...";

}

void End::update(float deltaTime)
{
    UpdateMusicStream(mGameState.bgm);

    if (IsKeyPressed(KEY_E)){
        mGameState.dialogueStep++;

        switch (mGameState.dialogueStep){ // each frame in cases to modify
            case 1:
                mGameState.cutscene->setTexture(textureEnd2);
                mGameState.dialogueText = "";
                break;

            case 2:
                mGameState.cutscene->setTexture(textureEnd3);
                mGameState.dialogueText = "";
                break;
            

            case 3:
                mGameState.cutscene->setTexture(textureEnd4);
                mGameState.dialogueText = "I haven't looked at this day...";
                break;

            case 4:
                mGameState.cutscene->setTexture(textureEnd5);
                mGameState.dialogueText = "...in so long";
                break;

            case 5:
                mGameState.cutscene->setTexture(textureEnd6);
                mGameState.dialogueText = "She was so excited...";
                break;

            case 6:
                mGameState.cutscene->setTexture(textureEnd7);
                mGameState.dialogueText = "...she barely slept the night before";
                break;

            case 7:
                mGameState.cutscene->setTexture(textureEnd8);
                mGameState.dialogueText = "We couldn't stop smiling";
                break;

            case 8:
                mGameState.cutscene->setTexture(textureEnd9);
                mGameState.dialogueText = "It felt like her whole future was stretching\nout in front of her";
                break;

            case 9:
                mGameState.cutscene->setTexture(textureEnd10);
                mGameState.dialogueText = "";
                break;

            case 10:
                mGameState.cutscene->setTexture(textureEnd11);
                mGameState.dialogueText = "She told me";
                break;

            case 11:
                mGameState.cutscene->setTexture(textureEnd12);
                mGameState.dialogueText = "she couldn't wait to show us the campus";
                break;

            case 12:
                mGameState.cutscene->setTexture(textureEnd13);
                mGameState.dialogueText = "I remember thinking";
                break;

            case 13:
                mGameState.cutscene->setTexture(textureEnd14);
                mGameState.dialogueText = "We have so much time";
                break;

            case 14:
                mGameState.cutscene->setTexture(textureEnd15);
                mGameState.dialogueText = "I didn't want to face this page, because I'd\nhave to accept that I'm here...";
                break;

            case 15:
                mGameState.cutscene->setTexture(textureEnd16);
                mGameState.dialogueText = "I didn't want to face this page, because I'd\nhave to accept that I'm here...";
                break;

            case 16:
                mGameState.cutscene->setTexture(textureEnd17);
                mGameState.dialogueText = "I didn't want to face this page, because I'd\nhave to accept that I'm here...";
                break;
            
            case 17:
                mGameState.cutscene->setTexture(textureEnd18);
                mGameState.dialogueText = "I didn't want to face this page, because I'd\nhave to accept that I'm here...";
                break;

            case 18:
                mGameState.cutscene->setTexture(textureEnd19);
                mGameState.dialogueText = "...and they're not";
                break;

            case 19:
                mGameState.cutscene->setTexture(textureEnd20);
                mGameState.dialogueText = "I survived and for so long… that felt like a\npunishment";
                break;

            case 20:
                mGameState.cutscene->setTexture(textureEnd21);
                mGameState.dialogueText = "But they wouldn’t want me to fade away with\nthem";
                break;

            case 21:
                mGameState.cutscene->setTexture(textureEnd22);
                mGameState.dialogueText = "'cause I'm...";
                break;

            case 22:
                mGameState.nextSceneID = 0; // go back to the start screen
                break;

        }
    }
}

void End::render()
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

void End::shutdown()
{
    delete mGameState.bg;
    UnloadTexture(textureEnd1);
    UnloadTexture(textureEnd2);
    UnloadTexture(textureEnd3);
    UnloadTexture(textureEnd4);
    UnloadTexture(textureEnd5);
    UnloadTexture(textureEnd6);
    UnloadTexture(textureEnd7);
    UnloadTexture(textureEnd8);
    UnloadTexture(textureEnd9);
    UnloadTexture(textureEnd10);
    UnloadTexture(textureEnd11);
    UnloadTexture(textureEnd12);
    UnloadTexture(textureEnd13);
    UnloadTexture(textureEnd14);
    UnloadTexture(textureEnd15);
    UnloadTexture(textureEnd16);
    UnloadTexture(textureEnd17);
    UnloadTexture(textureEnd18);
    UnloadTexture(textureEnd19);
    UnloadTexture(textureEnd20);
    UnloadTexture(textureEnd21);
    UnloadTexture(textureEnd22);
    UnloadTexture(textureDialogueBox);

    UnloadMusicStream(mGameState.bgm);
}
