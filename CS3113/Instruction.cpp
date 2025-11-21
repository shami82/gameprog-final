#include "Instruction.h"

Instruction::Instruction() : Scene({0.0f}, nullptr) {}
Instruction::Instruction(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Instruction::~Instruction() { shutdown(); }

void Instruction::initialise()
{
    textureBG = LoadTexture("assets/instructions.PNG");
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
}

void Instruction::update(float deltaTime)
{
    // UpdateMusicStream(mGameState.bgm);
    if (IsKeyPressed(KEY_ENTER)){ mGameState.nextSceneID = 2; } // go to attic
}

void Instruction::render()
{
    ClearBackground(BLACK);

    mGameState.bg->render();

    // // instr to start
    // const char* msg = "Press [Enter] to Start";
    // int fontSize = 30;
    // int textWidth = MeasureText(msg, fontSize);
    // DrawText(msg,
    //          static_cast<int>((mOrigin.x - textWidth / 2) + 10.0f),
    //          static_cast<int>(mOrigin.y + 85.0f),
    //          fontSize,
    //          WHITE);
}

void Instruction::shutdown()
{
    delete mGameState.bg;

    // UnloadMusicStream(mGameState.bgm);
}
