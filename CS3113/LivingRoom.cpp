#include "LivingRoom.h"

LivingRoom::LivingRoom() : Scene({0.0f}, nullptr) {}
LivingRoom::LivingRoom(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
LivingRoom::~LivingRoom() { shutdown(); }

void LivingRoom::initialise()
{
    textureBG = LoadTexture("assets/livingroom/livingroom.PNG");
    textureBG2 = LoadTexture("assets/livingroom/livingroom2.PNG");
    texturePlayer = LoadTexture("assets/player.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    textureCouch1 = LoadTexture("assets/livingroom/couch1.PNG");
    textureCouch2 = LoadTexture("assets/livingroom/couch2.PNG");;
    textureLivingBookShelf = LoadTexture("assets/livingroom/livingbookshelf.PNG");;
    textureLivingShelf = LoadTexture("assets/livingroom/livingshelf.PNG");;
    textureLivingStairs = LoadTexture("assets/livingroom/livingstairs.PNG");;
    textureLivingStool = LoadTexture("assets/livingroom/livingstool.PNG");;
    textureLivingTable = LoadTexture("assets/livingroom/livingtable.PNG");;
    textureLivingTV = LoadTexture("assets/livingroom/tv.PNG");;
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
    mGameState.bg->setColliderDimensions({ 
        645.0f ,
        490.0f
    });
    mGameState.bg->setColliderOffset({
        40.0f,
        30.0f
    });

    if (picPlaced){
        mGameState.bg->setTexture(textureBG2);
    }

    // ------------ PLAYER -------------
    std::map<Direction, std::vector<int>> playerAnimationAtlas = {
        {DOWN,  { 0,  1,  2,  3  }},
        {UP,    { 4,  5,  6,  7  }},
        {RIGHT, { 8,  9,  10, 11 }},
        {LEFT,  { 12, 13, 14, 15 }}
    };

    mGameState.player = new Entity(
        {700.0f, 155.0f},            // starting position
        {static_cast<float>(texturePlayer.width)/5.0f,
         static_cast<float>(texturePlayer.height)/5.0f},
        texturePlayer,
        ATLAS,
        { 4, 4 },                // sprite sheet dimensions
        playerAnimationAtlas,
        PLAYER
    );

    mGameState.player->setColliderDimensions({ 
        mGameState.player->getScale().x * 0.7f , // TODO: make little smaller?
        mGameState.player->getScale().y * 0.5f  // TODO: make little smaller?
    });
    mGameState.player->setColliderOffset({
        0.0f,
        mGameState.player->getScale().y * 0.25f // bottom half of the sprite
    });
    mGameState.player->setSpeed(130);
    mGameState.player->setDirection(LEFT); // facing the things in the room

    // ------------ COUCH1 -------------
    mGameState.couch1 = new Entity(
        {557.5f, 290.0f},
        {static_cast<float>(textureCouch1.width),
         static_cast<float>(textureCouch1.height)},
        textureCouch1,
        NONE
    );
    mGameState.couch1->setColliderDimensions({ 
        mGameState.couch1->getScale().x + 10.0f, // little bigger?
        mGameState.couch1->getScale().y + 10.0f
    });

    // ------------ COUCH2 -------------
    mGameState.couch2 = new Entity(
        {387.5f, 440.0f},
        {static_cast<float>(textureCouch2.width),
         static_cast<float>(textureCouch2.height)},
        textureCouch2,
        NONE
    );
    mGameState.couch2->setColliderDimensions({ 
        mGameState.couch2->getScale().x + 10.0f, // little bigger?
        mGameState.couch2->getScale().y + 10.0f
    });
    
    // ------------ LIVING BOOKSHELF -------------
    mGameState.livingbookshelf = new Entity(
        {230.0f, 185.0f},
        {static_cast<float>(textureLivingBookShelf.width),
         static_cast<float>(textureLivingBookShelf.height)},
        textureLivingBookShelf,
        NONE
    );
    mGameState.livingbookshelf->setColliderDimensions({ 
        mGameState.livingbookshelf->getScale().x + 10.0f, // little bigger?
        mGameState.livingbookshelf->getScale().y + 10.0f
    });
    
    // ------------ LIVING SHELF -------------
    mGameState.livingshelf = new Entity(
        {811.0f, 530.5f},
        {static_cast<float>(textureLivingShelf.width),
         static_cast<float>(textureLivingShelf.height)},
        textureLivingShelf,
        NONE
    );
    mGameState.livingshelf->setColliderDimensions({ 
        mGameState.livingshelf->getScale().x + 10.0f, // little bigger?
        mGameState.livingshelf->getScale().y + 10.0f
    });

    // ------------ LIVING TABLE -------------
    mGameState.livingtable = new Entity(
        {524.5f, 442.5f},
        {static_cast<float>(textureLivingTable.width),
         static_cast<float>(textureLivingTable.height)},
        textureLivingTable,
        NONE
    );
    mGameState.livingtable->setColliderDimensions({ 
        mGameState.livingtable->getScale().x + 10.0f, // little bigger?
        mGameState.livingtable->getScale().y + 10.0f
    });

    // ------------ LIVING STOOL -------------
    mGameState.livingstool = new Entity(
        {245.0f, 445.0f},
        {static_cast<float>(textureLivingStool.width),
         static_cast<float>(textureLivingStool.height)},
        textureLivingStool,
        NONE
    );
    mGameState.livingstool->setColliderDimensions({ 
        mGameState.livingstool->getScale().x + 10.0f, // little bigger?
        mGameState.livingstool->getScale().y + 10.0f
    });

    // ------------ LIVING TV -------------
    mGameState.livingtv = new Entity(
        {807.5f, 385.0f},
        {static_cast<float>(textureLivingTV.width),
         static_cast<float>(textureLivingTV.height)},
        textureLivingTV,
        NONE
    );
    mGameState.livingtv->setColliderDimensions({ 
        mGameState.livingtv->getScale().x + 10.0f, // little bigger?
        mGameState.livingtv->getScale().y + 10.0f
    });
    
    // ------------ LIVING STAIRS -------------
    mGameState.livingstairs = new Entity(
        {835.0f, 182.5f},
        {static_cast<float>(textureLivingStairs.width),
         static_cast<float>(textureLivingStairs.height)},
        textureLivingStairs,
        NONE
    );
    mGameState.livingstairs->setColliderDimensions({ 
        mGameState.livingstairs->getScale().x + 10.0f, // little bigger?
        mGameState.livingstairs->getScale().y + 10.0f
    });

    collidables.clear();
    collidables.push_back(mGameState.livingbookshelf);
    collidables.push_back(mGameState.couch1);
    collidables.push_back(mGameState.couch2);
    collidables.push_back(mGameState.livingstairs);
    collidables.push_back(mGameState.livingshelf);
    collidables.push_back(mGameState.livingtv);
    collidables.push_back(mGameState.livingstool);
    collidables.push_back(mGameState.livingtable);

    // ------------ DIALOGUE -------------
    Vector2 dialoguePos = { mOrigin.x , 720.0f - 20.0f - 100.0f }; 

    mGameState.dialoguebox = new Entity(
        dialoguePos,
        {775.0f, 155.0f},
        textureDialogueBox,
        NONE
    );

    if (!Scene::getPuz2Status()){
        if (!firstTimeDialoguePlayed){ // entering room for first time
            waitingForIntroDialogue = true;
            dialogueDelayTimer = 0.0f;
            firstTimeDialoguePlayed = true;
        }
    }

}

void LivingRoom::update(float deltaTime)
{
    // UpdateMusicStream(mGameState.bgm);

    // TODO: add the E key interact thing for the dialogue
    if (waitingForIntroDialogue){ // timer before intro dialogue
        dialogueDelayTimer += deltaTime;

        if (dialogueDelayTimer >= 0.2f){
            waitingForIntroDialogue = false;
            int screenW = GetScreenWidth();
            int screenH = GetScreenHeight();
            mGameState.dialogueActive = true;
            mGameState.dialogueStep = 0;
            mGameState.dialogueText =
                "Something's missing here...";
            
            return;
        }
    }

    mGameState.player->update(deltaTime,
                          mGameState.player,
                          collidables,
                          (int)collidables.size(),
                          mGameState.bg);
    if (IsKeyDown(KEY_A)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_D)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_W)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_S)) mGameState.player->animate(deltaTime);

    bool nearCouch1 = mGameState.player->isColliding(mGameState.couch1);
    bool nearCouch2 = mGameState.player->isColliding(mGameState.couch2);
    bool nearBookShelf = mGameState.player->isColliding(mGameState.livingbookshelf);
    bool nearShelf = mGameState.player->isColliding(mGameState.livingshelf);
    bool nearTable = mGameState.player->isColliding(mGameState.livingtable);
    bool nearTV = mGameState.player->isColliding(mGameState.livingtv);
    bool nearStool = mGameState.player->isColliding(mGameState.livingstool);
    bool nearStairs = mGameState.player->isColliding(mGameState.livingstairs);

    bool picFound = Scene::getPicFound();
    bool picPlaced = Scene::getPicPlaced();

    if (IsKeyPressed(KEY_E) && mGameState.dialogueActive){
        if (nearStool && stoolActivated){
            if (stoolActivated && mGameState.dialogueActive){
                if (mGameState.dialogueStep == 0){
                    mGameState.dialogueStep = 1;
                    mGameState.dialogueText = "I need to find it";
                    return;
                }
                else if (mGameState.dialogueStep == 1){
                    mGameState.dialogueActive = false;
                    mGameState.dialogueStep = 0;
                    if (hidingSpot == -1)
                        hidingSpot = (rand() % 6) + 1;

                    return;
                }
            }
        }
        else{
            mGameState.dialogueActive = false;
            mGameState.dialogueStep = 0;
            return;
        }
    }

    if (IsKeyPressed(KEY_E) && !mGameState.dialogueActive){
        if (nearStairs){ // can't leave unless clues are found (maybe change? not needed)
            if(picPlaced){ // could just go to hallway bcuz saved
                mGameState.nextSceneID = 4; // go to hallway
                return;
            }
            else{
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "I haven't gotten it yet";
                mGameState.dialogueStep = 0;
                return;
            }
        }
        if (nearStool){
            if (picFound && !picPlaced){ // if pic found then place the pic
                Scene::setPicPlacedStatus(true);
                mGameState.bg->setTexture(textureBG2);
                mGameState.nextSceneID = 10; // go to clue2
                return;
            }
            if (!stoolActivated){
                stoolActivated = true;
                mGameState.dialogueActive = true;
                mGameState.dialogueStep = 0;
                mGameState.dialogueText = "Oh.. our picture";
                return;
            }
        }

        // nothing should be interactable until the stool is interacted with
        if (!stoolActivated) return;

        // all the hiding spots
        if (!picFound){
            if (nearCouch1){ // 1 for couch1
                if (hidingSpot == 1){
                    Scene::setPicFoundStatus(true);
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Ah... here it is";
                } 
                else{
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "No, it's not here";
                }
                return;
            }

            if (nearTable){ // 2 for table
                if (hidingSpot == 2){
                    Scene::setPicFoundStatus(true);
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Ah... here it is";
                }
                else{
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "No, it's not here";
                }
                return;
            }

            if (nearBookShelf){ // 3 for bookshelf
                if (hidingSpot == 3){
                    Scene::setPicFoundStatus(true);
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Ah... here it is";
                } 
                else{
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "No, it's not here";
                }
                return;
            }

            if (nearShelf){ // 4 for shelf
                if (hidingSpot == 4){
                    Scene::setPicFoundStatus(true);
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Ah... here it is";
                } 
                else{
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "No, it's not here";
                }
                return;
            }

            if (nearCouch2){ //5 for couch2
                if (hidingSpot == 5){
                    Scene::setPicFoundStatus(true);
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Ah... here it is";
                }
                else{
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "No, it's not here";
                }
                return;
            }

            if (nearTV){ // 6 for tv
                if (hidingSpot == 6){
                    Scene::setPicFoundStatus(true);
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Ah... here it is";
                }
                else{
                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "No, it's not here";
                }
                return;
            }
        }
    }

    // TODO: Add interaction stuff
    // TODO: Fix dialogue system so no double clicks
}

void LivingRoom::render()
{
    ClearBackground(BLACK);

    // TODO: ADD CAMERA THINGS? more to like zoom into that room instead of void
    mGameState.bg->render();
    // mGameState.bg->displayCollider();
    mGameState.couch1->render();
    // mGameState.couch1->displayCollider();
    mGameState.couch2->render();
    // mGameState.couch2->displayCollider();
    mGameState.livingbookshelf->render();
    // mGameState.livingbookshelf->displayCollider();
    mGameState.livingshelf->render();
    // mGameState.livingshelf->displayCollider();
    mGameState.livingtable->render();
    // mGameState.livingtable->displayCollider();
    mGameState.livingstool->render();
    // mGameState.livingstool->displayCollider();
    mGameState.livingtv->render();
    // mGameState.livingtv->displayCollider();
    mGameState.livingstairs->render();
    // mGameState.livingstairs->displayCollider();

    mGameState.player->render();
    // mGameState.player->displayCollider();

    if (mGameState.dialogueActive){
        mGameState.dialoguebox->render();

        int x = mGameState.dialoguebox->getPosition().x - mGameState.dialoguebox->getScale().x/2 + 35;
        int y = mGameState.dialoguebox->getPosition().y - mGameState.dialoguebox->getScale().y/2 + 35;

        DrawText(mGameState.dialogueText.c_str(), x, y, 24, WHITE);
    }

    bool canInteract = mGameState.player->isColliding(mGameState.couch1) ||
                       mGameState.player->isColliding(mGameState.couch2) ||
                       mGameState.player->isColliding(mGameState.livingbookshelf) ||
                       mGameState.player->isColliding(mGameState.livingshelf) ||
                       mGameState.player->isColliding(mGameState.livingtable) ||
                       mGameState.player->isColliding(mGameState.livingstool) ||
                       mGameState.player->isColliding(mGameState.livingtv) ||
                       mGameState.player->isColliding(mGameState.livingstairs) ||
                       mGameState.dialogueActive;

    if (canInteract){
        const char* hint = "[E] to Interact";
        int size = 20;
        int tw = MeasureText(hint, size);

        DrawText(hint,
            GetScreenWidth() - tw - 20,
            GetScreenHeight() - size - 20,
            size,
            WHITE);
    }
    
}

void LivingRoom::shutdown()
{
    delete mGameState.bg;
    delete mGameState.player;
    delete mGameState.couch1;
    delete mGameState.couch2;
    delete mGameState.livingbookshelf;
    delete mGameState.livingshelf;
    delete mGameState.livingstairs;
    delete mGameState.livingstool;
    delete mGameState.livingtable;
    delete mGameState.livingtv;

    UnloadTexture(textureDialogueBox);
    // UnloadMusicStream(mGameState.bgm);
}
