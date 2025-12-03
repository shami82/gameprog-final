#include "BadEnd.h"

BadEnd::BadEnd() : Scene({0.0f}, nullptr) {}
BadEnd::BadEnd(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
BadEnd::~BadEnd() { shutdown(); }

void BadEnd::initialise()
{
    textureBG = LoadTexture("assets/cutsceneoverlay.PNG");
    textureBad1 = LoadTexture("assets/badend/bad1.PNG");
    textureBad2 = LoadTexture("assets/badend/bad2.PNG");
    textureBad3 = LoadTexture("assets/badend/bad3.PNG");
    textureBad4 = LoadTexture("assets/badend/bad4.PNG");
    textureBad5 = LoadTexture("assets/badend/bad5.PNG");
    textureBad6 = LoadTexture("assets/badend/bad6.PNG");
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
        textureBad1,                                      // texture file address
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

void BadEnd::update(float deltaTime)
{
    if (IsKeyPressed(KEY_E)){
        mGameState.dialogueStep++;

        switch (mGameState.dialogueStep){ // each frame in cases to modify
            case 1:
            mGameState.cutscene->setTexture(textureBad2);
            mGameState.dialogueText = "i can't";
            break;

            case 2:
            mGameState.cutscene->setTexture(textureBad3);
            mGameState.dialogueText = "i can't do this anymore";
            break;

            case 3:
            mGameState.cutscene->setTexture(textureBad4);
            mGameState.dialogueText = "";
            break;

            case 4:
            mGameState.cutscene->setTexture(textureBad5);
            mGameState.dialogueText = "maybe";
            break;

            case 5:
            mGameState.cutscene->setTexture(textureBad6);
            mGameState.dialogueText = "i'll try again tomorrow";
            break;

            case 6:
            mGameState.nextSceneID = 0; // go back to the start screen
            break;
        }
    }
}

void BadEnd::render()
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

void BadEnd::shutdown()
{
    delete mGameState.bg;
    UnloadTexture(textureBad1);
    UnloadTexture(textureBad2);
    UnloadTexture(textureBad3);
    UnloadTexture(textureBad4);
    UnloadTexture(textureBad5);
    UnloadTexture(textureBad6);
    UnloadTexture(textureDialogueBox);
}
