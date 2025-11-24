#include "Intro.h"

Intro::Intro() : Scene({0.0f}, nullptr) {}
Intro::Intro(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Intro::~Intro() { shutdown(); }

void Intro::initialise()
{
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");

    mGameState.dialogueActive = true;
    mGameState.dialogueStep   = 0;
    mGameState.dialogueText   = "I've been putting it off for too long";

    mGameState.nextSceneID = -1;

    mGameState.dialoguebox = new Entity(
        { mOrigin.x, 600.0f },
        { 775.0f, 155.0f },
        textureDialogueBox,
        NONE
    );

}

void Intro::update(float deltaTime)
{
    if (IsKeyPressed(KEY_E)){
        mGameState.dialogueStep++;

        if (mGameState.dialogueStep == 1){
            mGameState.dialogueText =
                "There's only so much time that I can stay like this...";
        }
        else if (mGameState.dialogueStep == 2){
            mGameState.dialogueText = "...today has to be the day";
        }
        else if (mGameState.dialogueStep == 3){ // finished dialogue go to attic
            mGameState.dialogueActive = false;
            mGameState.nextSceneID = 3;
            return;
        }
    }
}

void Intro::render()
{
    ClearBackground(BLACK);

    mGameState.dialoguebox->render();

    int textX = mOrigin.x - 350;
    int textY = 600 - 50;

    DrawText(
        mGameState.dialogueText.c_str(),
        textX, textY,
        24,
        WHITE
    );

    if (mGameState.dialogueActive){ // show the text that you can interact
        const char* hint = "[E] to Interact";
        int fontSize = 20;

        int padding = 20;
        int textWidth = MeasureText(hint, fontSize);

        int drawX = GetScreenWidth() - textWidth - padding;
        int drawY = GetScreenHeight() - fontSize - padding;

        DrawText(hint, drawX, drawY, fontSize, WHITE);
    }
}

void Intro::shutdown()
{
    UnloadTexture(textureDialogueBox);
}
