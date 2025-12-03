#include "HerRoom.h"

HerRoom::HerRoom() : Scene({0.0f}, nullptr) {}
HerRoom::HerRoom(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
HerRoom::~HerRoom() { shutdown(); }

void HerRoom::initialise()
{
    textureBG = LoadTexture("assets/herroom/herroom.PNG");
    texturePlayer = LoadTexture("assets/player.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    textureHerBed = LoadTexture("assets/herroom/herbed.PNG");
    textureBookshelf = LoadTexture("assets/herroom/bookshelf.PNG");
    textureHerChair = LoadTexture("assets/herroom/herchair.PNG");
    textureHerTable = LoadTexture("assets/herroom/hertable.PNG");
    textureHerShelf = LoadTexture("assets/herroom/shelf.PNG");
    textureHallwayDoor = LoadTexture("assets/herroom/hallwaydoor.PNG");
    textureBeanbag = LoadTexture("assets/herroom/beanbag.PNG");
    texturePolaroids = LoadTexture("assets/herroom/polaroids.PNG");
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
        630.0f ,
        405.0f
    });
    mGameState.bg->setColliderOffset({
        0.0f,
        62.5f
    });

    // ------------ PLAYER -------------
    std::map<Direction, std::vector<int>> playerAnimationAtlas = {
        {DOWN,  { 0,  1,  2,  3  }},
        {UP,    { 4,  5,  6,  7  }},
        {RIGHT, { 8,  9,  10, 11 }},
        {LEFT,  { 12, 13, 14, 15 }}
    };

    mGameState.player = new Entity(
        {600.0f, 535.0f},            // starting position
        {static_cast<float>(texturePlayer.width)/4.0f,
         static_cast<float>(texturePlayer.height)/4.0f},
        texturePlayer,
        ATLAS,
        { 4, 4 },                // sprite sheet dimensions
        playerAnimationAtlas,
        PLAYER
    );

    mGameState.player->setColliderDimensions({ 
        mGameState.player->getScale().x * 0.5f , // TODO: make little smaller?
        mGameState.player->getScale().y * 0.4f  // TODO: make little smaller?
    });
    mGameState.player->setColliderOffset({
        0.0f,
        mGameState.player->getScale().y * 0.25f // bottom half of the sprite
    });
    mGameState.player->setSpeed(150);
    mGameState.player->setDirection(UP); // facing the things in the room

    // ------------ HER BED -------------
    mGameState.herbed = new Entity(
        {500.0f, 265.0f},
        {static_cast<float>(textureHerBed.width),
         static_cast<float>(textureHerBed.height)},
        textureHerBed,
        NONE
    );
    mGameState.herbed->setColliderDimensions({ 
        mGameState.herbed->getScale().x + 10.0f, // little bigger?
        mGameState.herbed->getScale().y + 10.0f
    });
    
    // ------------ BOOKSHELF -------------
    mGameState.bookshelf = new Entity(
        {715.0f, 185.0f},
        {static_cast<float>(textureBookshelf.width),
         static_cast<float>(textureBookshelf.height)},
        textureBookshelf,
        NONE
    );
    mGameState.bookshelf->setColliderDimensions({ 
        mGameState.bookshelf->getScale().x + 10.0f, // little bigger?
        mGameState.bookshelf->getScale().y + 10.0f
    });
    
    // ------------ HER CHAIR -------------
    mGameState.herchair = new Entity(
        {316.5f, 482.5f},
        {static_cast<float>(textureHerChair.width),
         static_cast<float>(textureHerChair.height)},
        textureHerChair,
        NONE
    );
    mGameState.herchair->setColliderDimensions({ 
        mGameState.herchair->getScale().x + 10.0f, // little bigger?
        mGameState.herchair->getScale().y + 10.0f
    });

    // ------------ HER TABLE -------------
    mGameState.hertable = new Entity(
        {237.5f, 500.0f},
        {static_cast<float>(textureHerTable.width),
         static_cast<float>(textureHerTable.height)},
        textureHerTable,
        NONE
    );
    mGameState.hertable->setColliderDimensions({ 
        mGameState.hertable->getScale().x + 10.0f, // little bigger?
        mGameState.hertable->getScale().y + 10.0f
    });

    // ------------ SHELF -------------
    mGameState.hershelf = new Entity(
        {762.5f, 360.0f},
        {static_cast<float>(textureHerShelf.width),
         static_cast<float>(textureHerShelf.height)},
        textureHerShelf,
        NONE
    );
    mGameState.hershelf->setColliderDimensions({ 
        mGameState.hershelf->getScale().x + 10.0f, // little bigger?
        mGameState.hershelf->getScale().y + 10.0f
    });

    // ------------ BEANBAG -------------
    mGameState.beanbag = new Entity(
        {285.0f, 262.5f},
        {static_cast<float>(textureBeanbag.width),
         static_cast<float>(textureBeanbag.height)},
        textureBeanbag,
        NONE
    );
    mGameState.beanbag->setColliderDimensions({ 
        mGameState.beanbag->getScale().x + 10.0f, // little bigger?
        mGameState.beanbag->getScale().y + 10.0f
    });
    
    // ------------ HALLWAY DOOR -------------
    mGameState.herhallwaydoor = new Entity(
        {670.0f, 620.0f},
        {static_cast<float>(textureHallwayDoor.width),
         static_cast<float>(textureHallwayDoor.height)},
        textureHallwayDoor,
        NONE
    );
    mGameState.herhallwaydoor->setColliderDimensions({ 
        mGameState.herhallwaydoor->getScale().x + 10.0f, // little bigger?
        mGameState.herhallwaydoor->getScale().y + 10.0f
    });

    // ------------ POLAROIDS -------------
    mGameState.polaroids = new Entity(
        {-900.0f, -900.0f}, // super off screen rn
        {static_cast<float>(texturePolaroids.width),
         static_cast<float>(texturePolaroids.height)},
        texturePolaroids,
        NONE
    );

    mGameState.polaroids->setColliderDimensions({
        mGameState.polaroids->getScale().x + 10.0f,
        mGameState.polaroids->getScale().y + 10.0f
    });

    collidables.clear();
    collidables.push_back(mGameState.herhallwaydoor);
    collidables.push_back(mGameState.beanbag);
    collidables.push_back(mGameState.hershelf);
    collidables.push_back(mGameState.hertable);
    collidables.push_back(mGameState.herchair);
    collidables.push_back(mGameState.bookshelf);
    collidables.push_back(mGameState.herbed);

    // ------------ DIALOGUE -------------
    Vector2 dialoguePos = { mOrigin.x , 720.0f - 20.0f - 100.0f }; 

    mGameState.dialoguebox = new Entity(
        dialoguePos,
        {775.0f, 155.0f},
        textureDialogueBox,
        NONE
    );

    if (!Scene::getPuz1Status()){
        if (!firstTimeDialoguePlayed){ // entering room for first time
            waitingForIntroDialogue = true;
            dialogueDelayTimer = 0.0f;
            firstTimeDialoguePlayed = true;
        }
    }

}

void HerRoom::update(float deltaTime)
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
                "I haven't been here in a while...";
            
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

    static bool completedPuz1 = Scene::getPuz1Status();

    bool nearHallwayDoor = mGameState.player->isColliding(mGameState.herhallwaydoor);
    bool nearBed = mGameState.player->isColliding(mGameState.herbed);
    bool nearShelf = mGameState.player->isColliding(mGameState.hershelf);
    bool nearTable = mGameState.player->isColliding(mGameState.hertable);
    bool nearChair = mGameState.player->isColliding(mGameState.herchair);
    bool nearBeanbag = mGameState.player->isColliding(mGameState.beanbag);
    bool nearBookshelf = mGameState.player->isColliding(mGameState.bookshelf);
    bool nearPolaroids = mGameState.player->isColliding(mGameState.polaroids);

    bool pol1 = Scene::getPol1Status();
    bool pol2 = Scene::getPol2Status();
    bool pol3 = Scene::getPol3Status();
    bool pol4 = Scene::getPol4Status();

    if (mGameState.dialogueActive && IsKeyPressed(KEY_E)){
        mGameState.dialogueActive = false;
        mGameState.dialogueStep = 0;
        return;
    }

    if (IsKeyPressed(KEY_E) && !mGameState.dialogueActive){
        if (nearPolaroids){ // when the polaroids are there, send to first clue scene
            mGameState.nextSceneID = 6; // TODO: CHANGE TO CLUE SCENE
            return;
        }
        if (nearHallwayDoor){ // can't leave unless clues are found (maybe change? not needed)
            if(pol1 && pol2 && pol3 && pol4){ // could just go to hallway bcuz saved
                mGameState.nextSceneID = 4; // go to hallway
                return;
            }
            else{
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "I haven't found everything yet";
                mGameState.dialogueStep = 0;
                return;
            }
        }
        if (nearShelf && !pol1){ // finding the first polaroid
            Scene::setPol1Status(true);
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "I found the first polaroid.";
            mGameState.dialogueStep = 0;
            return;
        }
        if (nearTable && !pol2){ // finding the second polaroid
            Scene::setPol2Status(true);
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "I found the second polaroid.";
            mGameState.dialogueStep = 0;
            return;
        }
        if (nearBed && !pol3){ // finding the third polaroid
            Scene::setPol3Status(true);
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "I found the third polaroid.";
            mGameState.dialogueStep = 0;
            return;
        }
        if (nearBeanbag && !pol4){ // finding the second polaroid
            Scene::setPol4Status(true);
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "I found the fourth polaroid.";
            mGameState.dialogueStep = 0;
            return;
        }
        if (nearChair || nearBookshelf){ // decoys
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "I don't think it was here.";
            mGameState.dialogueStep = 0;
            return;
        }

    }

    if (pol1 && pol2 && pol3 && pol4){ // move onto screen once
        if (mGameState.polaroids->getPosition().x < 0){
            mGameState.polaroids->setPosition({ 630.0f, 450.0f });  
        }
    }

    // TODO: Add interaction stuff
    // TODO: Fix dialogue system so no double clicks
}

void HerRoom::render()
{
    ClearBackground(BLACK);

    // TODO: ADD CAMERA THINGS? more to like zoom into that room instead of void
    mGameState.bg->render();
    // mGameState.bg->displayCollider();
    mGameState.herbed->render();
    // mGameState.herbed->displayCollider();
    mGameState.hershelf->render();
    // mGameState.hershelf->displayCollider();
    mGameState.bookshelf->render();
    // mGameState.bookshelf->displayCollider();
    mGameState.herchair->render();
    // mGameState.herchair->displayCollider();
    mGameState.hertable->render();
    // mGameState.hertable->displayCollider();
    mGameState.beanbag->render();
    // mGameState.beanbag->displayCollider();
    mGameState.herhallwaydoor->render();
    // mGameState.herhallwaydoor->displayCollider();
    mGameState.polaroids->render();
    // mGameState.polaroids->displayCollider();

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

    bool nearHallwayDoor = mGameState.player->isColliding(mGameState.herhallwaydoor);
    bool nearBed = mGameState.player->isColliding(mGameState.herbed);
    bool nearShelf = mGameState.player->isColliding(mGameState.hershelf);
    bool nearTable = mGameState.player->isColliding(mGameState.hertable);
    bool nearChair = mGameState.player->isColliding(mGameState.herchair);
    bool nearBeanbag = mGameState.player->isColliding(mGameState.beanbag);
    bool nearBookshelf = mGameState.player->isColliding(mGameState.bookshelf);
    bool nearPolaroids = mGameState.player->isColliding(mGameState.polaroids);
    bool pol1 = Scene::getPol1Status();
    bool pol2 = Scene::getPol2Status();
    bool pol3 = Scene::getPol3Status();
    bool pol4 = Scene::getPol4Status();

    if (nearHallwayDoor || (nearBed && !pol3) || (nearShelf && !pol1) || (nearTable && !pol2) || nearChair ||
        (nearBeanbag && !pol4) || nearBookshelf || nearPolaroids){
        int screenW = GetScreenWidth();
        int screenH = GetScreenHeight();
        const char *hint = "[E] to Interact";

        int textW = MeasureText(hint, 24);

        DrawText(
            hint,
            screenW - textW - 20,
            screenH - 20 - 24,
            24,
            WHITE
        );
    }
    
}

void HerRoom::shutdown()
{
    delete mGameState.bg;
    delete mGameState.player;
    delete mGameState.herbed;
    delete mGameState.bookshelf;
    delete mGameState.herchair;
    delete mGameState.hertable;
    delete mGameState.hershelf;
    delete mGameState.herhallwaydoor;
    delete mGameState.beanbag;
    delete mGameState.polaroids;

    UnloadTexture(textureDialogueBox);
    // UnloadMusicStream(mGameState.bgm);
}
