#include "Start.h"

Start::Start() : Scene({0.0f}, nullptr) {}
Start::Start(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Start::~Start() { shutdown(); }

void Start::initialise()
{
    textureBG = LoadTexture("assets/title.PNG");
    mGameState.nextSceneID = -1;

    mGameState.bgm = LoadMusicStream("assets/audio/farwell.mp3");
    SetMusicVolume(mGameState.bgm, 0.40f);
    PlayMusicStream(mGameState.bgm);

    mGameState.bg = new Entity(
        mOrigin,                                        // position
        { 990.0f, 720.0f },                             // size
        textureBG,                                      // texture file address
        NONE                                            // type
    );

    Scene::setPuz1Status(false);
    Scene::setPuz2Status(false);
    Scene::setPuz3Status(false);

    // for puzzle 1
    Scene::setPol1Status(false);
    Scene::setPol2Status(false);
    Scene::setPol3Status(false);
    Scene::setPol4Status(false);
    
    // for puzzle 2
    Scene::setPicFoundStatus(false);
    Scene::setPicPlacedStatus(false);

    // for puzzle 3
    Scene::setKeyFoundStatus(false);
}

void Start::update(float deltaTime)
{
    UpdateMusicStream(mGameState.bgm);
    if (IsKeyPressed(KEY_ENTER)){ mGameState.nextSceneID = 1; } // go to instructions
}

void Start::render()
{
    ClearBackground(BLACK);

    mGameState.bg->render();

}

void Start::shutdown()
{
    delete mGameState.bg;

    UnloadMusicStream(mGameState.bgm);
}
