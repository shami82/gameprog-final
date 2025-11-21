#include "Attic.h"

Attic::Attic() : Scene({0.0f}, nullptr) {}
Attic::Attic(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Attic::~Attic() { shutdown(); }

void Attic::initialise()
{
    textureBG = LoadTexture("assets/attic/attic.PNG");
    texturePlayer = LoadTexture("assets/player.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    textureAtticDoor = LoadTexture("assets/attic/atticdoor.PNG");
    textureChest = LoadTexture("assets/attic/chest1.PNG");
    textureWardrobe = LoadTexture("assets/attic/wardrobe1.PNG");
    textureAlbum = LoadTexture("assets/attic/album1.PNG");
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

    // ------------ PLAYER -------------
    std::map<Direction, std::vector<int>> playerAnimationAtlas = {
        {DOWN,  { 0,  1,  2,  3  }},
        {UP,    { 4,  5,  6,  7  }},
        {RIGHT, { 8,  9,  10, 11 }},
        {LEFT,  { 12, 13, 14, 15 }}
    };

    mGameState.player = new Entity(
        {600.0f, 535.0f},            // starting position
        {100.0f, 155.0f},        // player scale
        texturePlayer,
        ATLAS,
        { 4, 4 },                // sprite sheet dimensions
        playerAnimationAtlas,
        PLAYER
    );

    mGameState.player->setColliderDimensions({ 
        mGameState.player->getScale().x, // little smaller?
        mGameState.player->getScale().y
    });
    mGameState.player->setSpeed(150);
    mGameState.player->setDirection(UP); // facing the things in the room

    // ------------ WARDROBE -------------
    mGameState.wardrobe = new Entity(
        {352.5f, 180.0f},
        {static_cast<float>(textureWardrobe.width),
         static_cast<float>(textureWardrobe.height)},
        textureWardrobe,
        NONE
    );
    mGameState.wardrobe->setColliderDimensions({ 
        mGameState.wardrobe->getScale().x + 10.0f, // little bigger?
        mGameState.wardrobe->getScale().y + 10.0f
    });
    
    // ------------ CHEST -------------
    mGameState.chest = new Entity(
        {280.0f, 445.0f},
        {static_cast<float>(textureChest.width),
         static_cast<float>(textureChest.height)},
        textureChest,
        NONE
    );
    mGameState.chest->setColliderDimensions({ 
        mGameState.chest->getScale().x + 10.0f, // little bigger?
        mGameState.chest->getScale().y + 10.0f
    });
    
    // ------------ ALBUM -------------
    mGameState.album = new Entity(
        {705.0f, 305.0f},
        {static_cast<float>(textureAlbum.width),
         static_cast<float>(textureAlbum.height)},
        textureAlbum,
        NONE
    );
    mGameState.album->setColliderDimensions({ 
        mGameState.album->getScale().x + 10.0f, // little bigger?
        mGameState.album->getScale().y + 10.0f
    });
    
    // ------------ ATTIC DOOR -------------
    mGameState.atticdoor = new Entity(
        {655.0f, 655.0f},
        {static_cast<float>(textureAtticDoor.width),
         static_cast<float>(textureAtticDoor.height)},
        textureAtticDoor,
        NONE
    );
    mGameState.atticdoor->setColliderDimensions({ 
        mGameState.atticdoor->getScale().x + 10.0f, // little bigger?
        mGameState.atticdoor->getScale().y + 10.0f
    });

    // ------------ DIALOGUE -------------
    Vector2 dialoguePos = { mOrigin.x , 720.0f - 20.0f - 100.0f }; 

    mGameState.dialoguebox = new Entity(
        dialoguePos,
        {775.0f, 155.0f},
        textureDialogueBox,
        NONE
    );

}

void Attic::update(float deltaTime)
{
    // UpdateMusicStream(mGameState.bgm);
    mGameState.player->update(deltaTime, nullptr, nullptr, 0);
    if (IsKeyDown(KEY_A)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_D)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_W)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_S)) mGameState.player->animate(deltaTime);

    static bool completedPuz1 = false;
    static bool completedPuz2 = false;
    static bool completedPuz3 = false;

    bool nearChest = mGameState.player->isColliding(mGameState.chest);
    bool nearWardrobe = mGameState.player->isColliding(mGameState.wardrobe);
    bool nearAlbum = mGameState.player->isColliding(mGameState.album);
    bool nearAtticDoor = mGameState.player->isColliding(mGameState.atticdoor);

    if (IsKeyPressed(KEY_E)){
        if (mGameState.dialogueActive){
            // multiple dialogue things
            mGameState.dialogueStep++;
            if (mGameState.dialogueStep > 1){
                mGameState.dialogueActive = false;
                mGameState.dialogueStep = 0;
            }
        } 
        else{
            if (nearAtticDoor){ // leave to hallways
                mGameState.nextSceneID = 0; // TODO: CHANGE TO HALLWAY SCENE
                return;
            }
            if (nearChest && !completedPuz1){ // puz1 interaction
                mGameState.dialogueActive = true;
                mGameState.dialogueStep = 0;
                mGameState.dialogueText = "It's locked";
            } 
            else if ((nearWardrobe && !completedPuz2) || (nearAlbum && !completedPuz3)){ // no puz2 or 3 until 1 done
                mGameState.dialogueActive = true;
                mGameState.dialogueStep = 0;
                mGameState.dialogueText = "No.. not yet";
            }
        }
        if (mGameState.dialogueActive){
            if (nearChest && !completedPuz1){
                if (mGameState.dialogueStep == 1){
                    mGameState.dialogueText = "I need to remember the combination";
                }
            }
        }
    }

    // TODO: Add interaction stuff with atticdoor, chest, wardrobe, and album
    // TODO: Fix dialogue system

    if (IsKeyPressed(KEY_ENTER)){ mGameState.nextSceneID = 0; } // go to lvl 1
}

void Attic::render()
{
    ClearBackground(BLACK);

    // TODO: ADD CAMERA THINGS? more to like zoom into that room instead of void
    mGameState.bg->render();
    mGameState.bg->displayCollider();
    mGameState.wardrobe->render();
    mGameState.wardrobe->displayCollider();
    mGameState.chest->render();
    mGameState.chest->displayCollider();
    mGameState.album->render();
    mGameState.album->displayCollider();
    mGameState.atticdoor->render();
    mGameState.atticdoor->displayCollider();

    mGameState.player->render();
    mGameState.player->displayCollider();

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
    
}

void Attic::shutdown()
{
    delete mGameState.bg;
    delete mGameState.player;
    delete mGameState.atticdoor;
    delete mGameState.chest;
    delete mGameState.wardrobe;
    delete mGameState.album;

    UnloadTexture(textureDialogueBox);
    // UnloadMusicStream(mGameState.bgm);
}
