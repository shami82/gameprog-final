#include "Hallway.h"

Hallway::Hallway() : Scene({0.0f}, nullptr) {}
Hallway::Hallway(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Hallway::~Hallway() { shutdown(); }

void Hallway::initialise()
{
    textureBG = LoadTexture("assets/hallway/hallway.PNG");
    texturePlayer = LoadTexture("assets/player.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    textureAtticStairs = LoadTexture("assets/hallway/atticstairs.PNG");
    textureHerDoor = LoadTexture("assets/hallway/herdoor.PNG");
    textureBedroomDoor = LoadTexture("assets/hallway/bedroomdoor.PNG");
    textureLivingroomDoor = LoadTexture("assets/hallway/livingroomdoor.PNG");
    mGameState.nextSceneID = -1;

    mGameState.doorSound = LoadSound("assets/audio/door.wav");
    SetSoundVolume(mGameState.doorSound, 0.75f);

    mGameState.bg = new Entity(
        mOrigin,                                        // position
        { 990.0f, 720.0f },                             // size
        textureBG,                                      // texture file address
        NONE                                            // type
    );
    mGameState.bg->setColliderDimensions({ 
        990.0f ,
        240.0f
    });
    mGameState.bg->setColliderOffset({
        0.0f,
        80.0f
    });

    // ------------ PLAYER -------------
    std::map<Direction, std::vector<int>> playerAnimationAtlas = {
        {DOWN,  { 0,  1,  2,  3  }},
        {UP,    { 4,  5,  6,  7  }},
        {RIGHT, { 8,  9,  10, 11 }},
        {LEFT,  { 12, 13, 14, 15 }}
    };

    mGameState.player = new Entity(
        {mOrigin.x, mOrigin.y + 50.0f},            // starting position
        {static_cast<float>(texturePlayer.width)/4.0f,
         static_cast<float>(texturePlayer.height)/4.0f},
        texturePlayer,
        ATLAS,
        { 4, 4 },                // sprite sheet dimensions
        playerAnimationAtlas,
        PLAYER
    );

    mGameState.player->setColliderDimensions({ 
        mGameState.player->getScale().x * 0.9f , // TODO: make little smaller?
        mGameState.player->getScale().y * 0.5f  // TODO: make little smaller?
    });
    mGameState.player->setColliderOffset({
        0.0f,
        mGameState.player->getScale().y * 0.25f // bottom half of the sprite
    });
    mGameState.player->setSpeed(150);
    mGameState.player->setDirection(RIGHT); // facing the things in the room

    // ------------ ATTIC STAIRS -------------
    mGameState.atticstairs = new Entity(
        {19.0f, 417.5f},
        {static_cast<float>(textureAtticStairs.width),
         static_cast<float>(textureAtticStairs.height)},
        textureAtticStairs,
        NONE
    );
    mGameState.atticstairs->setColliderDimensions({ 
        mGameState.atticstairs->getScale().x + 10.0f, // little bigger?
        mGameState.atticstairs->getScale().y + 10.0f
    });
    
    // ------------ HER DOOR -------------
    mGameState.herdoor = new Entity(
        {333.5f, 247.5f},
        {static_cast<float>(textureHerDoor.width),
         static_cast<float>(textureHerDoor.height)},
        textureHerDoor,
        NONE
    );
    mGameState.herdoor->setColliderDimensions({ 
        mGameState.herdoor->getScale().x + 10.0f, // little bigger?
        mGameState.herdoor->getScale().y + 10.0f
    });
    
    // ------------ BEDROOM DOOR -------------
    mGameState.bedroomdoor = new Entity(
        {627.5f, 247.5f},
        {static_cast<float>(textureBedroomDoor.width),
         static_cast<float>(textureBedroomDoor.height)},
        textureBedroomDoor,
        NONE
    );
    mGameState.bedroomdoor->setColliderDimensions({ 
        mGameState.bedroomdoor->getScale().x + 10.0f, // little bigger?
        mGameState.bedroomdoor->getScale().y + 10.0f
    });
    
    // ------------ LIVINGROOM DOOR -------------
    mGameState.livingroomdoor = new Entity(
        {837.5f, 552.5f},
        {static_cast<float>(textureLivingroomDoor.width),
         static_cast<float>(textureLivingroomDoor.height)},
        textureLivingroomDoor,
        NONE
    );
    mGameState.livingroomdoor->setColliderDimensions({ 
        mGameState.livingroomdoor->getScale().x + 10.0f, // little bigger?
        mGameState.livingroomdoor->getScale().y + 10.0f
    });

    collidables.clear();
    collidables.push_back(mGameState.herdoor);
    collidables.push_back(mGameState.livingroomdoor);
    collidables.push_back(mGameState.bedroomdoor);
    collidables.push_back(mGameState.atticstairs);

    // ------------ DIALOGUE -------------
    Vector2 dialoguePos = { mOrigin.x , 720.0f - 20.0f - 100.0f }; 

    mGameState.dialoguebox = new Entity(
        dialoguePos,
        {775.0f, 155.0f},
        textureDialogueBox,
        NONE
    );

}

void Hallway::update(float deltaTime)
{
    // UpdateMusicStream(mGameState.bgm);
   mGameState.player->update(deltaTime,
                          mGameState.player,
                          collidables,
                          (int)collidables.size(),
                          mGameState.bg);
    if (IsKeyDown(KEY_A)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_D)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_W)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_S)) mGameState.player->animate(deltaTime);

    bool nearAtticStairs = mGameState.player->isColliding(mGameState.atticstairs);
    bool nearHerDoor = mGameState.player->isColliding(mGameState.herdoor);
    bool nearBedroomDoor = mGameState.player->isColliding(mGameState.bedroomdoor);
    bool nearLivingroomDoor = mGameState.player->isColliding(mGameState.livingroomdoor);

    if (mGameState.dialogueActive && IsKeyPressed(KEY_E)){
        mGameState.dialogueActive = false;
        mGameState.dialogueStep = 0;
        return;
    }

    if (IsKeyPressed(KEY_E)){
        if (nearAtticStairs){
            mGameState.nextSceneID = 3; // go to attic
            return;
        }
        if (nearHerDoor){
            PlaySound(mGameState.doorSound);
            mGameState.nextSceneID = 5; // TODO: CHANGE TO HER ROOM
            return;
        }
        if (nearLivingroomDoor){
            if (!Scene::getPuz1Status()){ // can only go after puzzle 2 complete
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "Wait, no, this isn't the place";
                return;
            }
            mGameState.nextSceneID = 9; // TODO: CHANGE TO LIVINGROOM
            return;
        }
        if (nearBedroomDoor){
            if (!Scene::getPuz2Status()){ // can only go after puzzle 1 complete
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "Wait, no, this isn't the place";
                return;
            }
            PlaySound(mGameState.doorSound);
            mGameState.nextSceneID = 12; // TODO: CHANGE TO BEDROOM
            return;
        }
    }

    // TODO: Decide if interaction will stay guided or not
    // TODO: Fix dialogue system so no double clicks
}

void Hallway::render()
{
    ClearBackground(BLACK);

    // TODO: ADD CAMERA THINGS? more to like zoom into that room instead of void
    mGameState.bg->render();
    // mGameState.bg->displayCollider();
    mGameState.atticstairs->render();
    // mGameState.atticstairs->displayCollider();
    mGameState.herdoor->render();
    // mGameState.herdoor->displayCollider();
    mGameState.bedroomdoor->render();
    // mGameState.bedroomdoor->displayCollider();
    mGameState.livingroomdoor->render();
    // mGameState.livingroomdoor->displayCollider();

    mGameState.player->render();
    // mGameState.player->displayCollider();

    if (mGameState.dialogueActive){
        mGameState.dialoguebox->render();
        
        int textX = static_cast<int>(mGameState.dialoguebox->getPosition().x - mGameState.dialoguebox->getScale().x / 2 + 35);
        int textY = static_cast<int>(mGameState.dialoguebox->getPosition().y - mGameState.dialoguebox->getScale().y / 2 + 35);

        DrawText(
            mGameState.dialogueText.c_str(), 
            textX, textY, 
            24, 
            WHITE
        );
    }

    bool nearAtticStairs = mGameState.player->isColliding(mGameState.atticstairs);
    bool nearHerDoor = mGameState.player->isColliding(mGameState.herdoor);
    bool nearBedroomDoor = mGameState.player->isColliding(mGameState.bedroomdoor);
    bool nearLivingroomDoor = mGameState.player->isColliding(mGameState.livingroomdoor);

    bool canInteract =
        nearAtticStairs || nearHerDoor || nearBedroomDoor || nearLivingroomDoor ||
        mGameState.dialogueActive;

    if (canInteract)
    {
        const char* hint = "[E] to Interact";
        int fontSize = 20;

        int padding = 20;
        int textWidth = MeasureText(hint, fontSize);

        int drawX = GetScreenWidth() - textWidth - padding;
        int drawY = GetScreenHeight() - fontSize - padding;

        DrawText(hint, drawX, drawY, fontSize, WHITE);
    }
    
}

void Hallway::shutdown()
{
    delete mGameState.bg;
    delete mGameState.player;
    delete mGameState.atticstairs;
    delete mGameState.herdoor;
    delete mGameState.bedroomdoor;
    delete mGameState.livingroomdoor;

    UnloadTexture(textureDialogueBox);
    
    UnloadSound(mGameState.doorSound);
}
