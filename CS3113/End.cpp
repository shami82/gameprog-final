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
    UnloadTexture(textureDialogueBox);
}
