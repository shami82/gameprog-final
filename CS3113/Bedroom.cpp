#include "Bedroom.h"

Bedroom::Bedroom() : Scene({0.0f}, nullptr) {}
Bedroom::Bedroom(Vector2 origin, const char *bgHexCode) : Scene(origin, bgHexCode) {}
Bedroom::~Bedroom() { shutdown(); }

void Bedroom::initialise()
{
    textureBG = LoadTexture("assets/bedroom/bedroom.PNG");
    texturePlayer = LoadTexture("assets/player.PNG");
    textureDialogueBox = LoadTexture("assets/dialoguebox.PNG");
    textureBedroomBed = LoadTexture("assets/bedroom/bedroombed.PNG");;
    textureBedroomDresser = LoadTexture("assets/bedroom/bedroomdresser.PNG");;
    textureBedroomShelves = LoadTexture("assets/bedroom/bedroomshelves.PNG");;
    textureBedroomTable = LoadTexture("assets/bedroom/bedroomtable.PNG");;
    textureBedroomWardrobe = LoadTexture("assets/bedroom/bedroomwardrobe.PNG");;
    textureHallwayDoor = LoadTexture("assets/bedroom/hallwaydoor.PNG");;
    textureMirror = LoadTexture("assets/bedroom/mirror.PNG");;
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
    mGameState.bg->setColliderDimensions({  // TODO: NEED TO UPDATE
        670.0f ,
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
        {420.0f, 535.0f},            // starting position
        {static_cast<float>(texturePlayer.width)/4.5f,
         static_cast<float>(texturePlayer.height)/4.5f},
        texturePlayer,
        ATLAS,
        { 4, 4 },                // sprite sheet dimensions
        playerAnimationAtlas,
        PLAYER
    );

    mGameState.player->setColliderDimensions({ 
        mGameState.player->getScale().x * 0.7f , // TODO: make little smaller?
        mGameState.player->getScale().y * 0.4f  // TODO: make little smaller?
    });
    mGameState.player->setColliderOffset({
        0.0f,
        mGameState.player->getScale().y * 0.25f // bottom half of the sprite
    });
    mGameState.player->setSpeed(90); // slower for the vibes
    mGameState.player->setDirection(UP); // facing the things in the room

    // ------------ BED -------------
    mGameState.bedroombed = new Entity(
        {720.0f, 400.0f},
        {static_cast<float>(textureBedroomBed.width),
         static_cast<float>(textureBedroomBed.height)},
        textureBedroomBed,
        NONE
    );
    mGameState.bedroombed->setColliderDimensions({ 
        mGameState.bedroombed->getScale().x + 10.0f, // little bigger?
        mGameState.bedroombed->getScale().y + 10.0f
    });
    
    // ------------ DRESSER -------------
    mGameState.bedroomdresser = new Entity(
        {225.0f, 470.0f},
        {static_cast<float>(textureBedroomDresser.width),
         static_cast<float>(textureBedroomDresser.height)},
        textureBedroomDresser,
        NONE
    );
    mGameState.bedroomdresser->setColliderDimensions({ 
        mGameState.bedroomdresser->getScale().x + 10.0f, // little bigger?
        mGameState.bedroomdresser->getScale().y + 10.0f
    });
    
    // ------------ SHELVES -------------
    mGameState.bedroomshelves = new Entity(
        {786.0f, 400.0f},
        {static_cast<float>(textureBedroomShelves.width),
         static_cast<float>(textureBedroomShelves.height)},
        textureBedroomShelves,
        NONE
    );
    mGameState.bedroomshelves->setColliderDimensions({ 
        mGameState.bedroomshelves->getScale().x + 10.0f, // little bigger?
        mGameState.bedroomshelves->getScale().y + 10.0f
    });

    // ------------ TABLE -------------
    mGameState.bedroomtable = new Entity(
        {440.0f, 222.5f},
        {static_cast<float>(textureBedroomTable.width),
         static_cast<float>(textureBedroomTable.height)},
        textureBedroomTable,
        NONE
    );
    mGameState.bedroomtable->setColliderDimensions({ 
        mGameState.bedroomtable->getScale().x + 10.0f, // little bigger?
        mGameState.bedroomtable->getScale().y + 10.0f
    });

    // ------------ WARDROBE -------------
    mGameState.bedroomwardrobe = new Entity(
        {190.0f, 257.5f},
        {static_cast<float>(textureBedroomWardrobe.width),
         static_cast<float>(textureBedroomWardrobe.height)},
        textureBedroomWardrobe,
        NONE
    );
    mGameState.bedroomwardrobe->setColliderDimensions({ 
        mGameState.bedroomwardrobe->getScale().x + 10.0f, // little bigger?
        mGameState.bedroomwardrobe->getScale().y + 10.0f
    });

    // ------------ MIRROR -------------
    mGameState.bedroommirror = new Entity(
        {680.0f, 172.5f},
        {static_cast<float>(textureMirror.width),
         static_cast<float>(textureMirror.height)},
        textureMirror,
        NONE
    );
    mGameState.bedroommirror->setColliderDimensions({ 
        mGameState.bedroommirror->getScale().x + 10.0f, // little bigger?
        mGameState.bedroommirror->getScale().y + 10.0f
    });
    
    // ------------ HALLWAY DOOR -------------
    mGameState.hallwaydoor = new Entity(
        {320.0f, 618.0f},
        {static_cast<float>(textureHallwayDoor.width)*0.85f,
         static_cast<float>(textureHallwayDoor.height)},
        textureHallwayDoor,
        NONE
    );
    mGameState.hallwaydoor->setColliderDimensions({ 
        mGameState.hallwaydoor->getScale().x + 10.0f, // little bigger?
        mGameState.hallwaydoor->getScale().y + 10.0f
    });

    collidables.clear();
    collidables.push_back(mGameState.hallwaydoor);
    collidables.push_back(mGameState.bedroombed);
    collidables.push_back(mGameState.bedroomdresser);
    collidables.push_back(mGameState.bedroomshelves);
    collidables.push_back(mGameState.bedroomtable);
    collidables.push_back(mGameState.bedroomwardrobe);
    collidables.push_back(mGameState.bedroommirror);
    collidables.push_back(mGameState.hallwaydoor);

    // ------------ DIALOGUE -------------
    Vector2 dialoguePos = { mOrigin.x , 720.0f - 20.0f - 100.0f }; 

    mGameState.dialoguebox = new Entity(
        dialoguePos,
        {775.0f, 155.0f},
        textureDialogueBox,
        NONE
    );

    if (!Scene::getPuz3Status()){
        if (!firstTimeDialoguePlayed){ // entering room for first time
            waitingForIntroDialogue = true;
            dialogueDelayTimer = 0.0f;
            firstTimeDialoguePlayed = true;
        }
    }

    mirrorInteracted = false;

}

void Bedroom::update(float deltaTime)
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
                "...";
            
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

    static bool completedPuz3 = Scene::getPuz3Status();

    bool nearHallwayDoor = mGameState.player->isColliding(mGameState.hallwaydoor);
    bool nearBed = mGameState.player->isColliding(mGameState.bedroombed);
    bool nearDresser = mGameState.player->isColliding(mGameState.bedroomdresser);
    bool nearShelves = mGameState.player->isColliding(mGameState.bedroomshelves);
    bool nearTable = mGameState.player->isColliding(mGameState.bedroomtable);
    bool nearWardrobe = mGameState.player->isColliding(mGameState.bedroomwardrobe);
    bool nearMirror = mGameState.player->isColliding(mGameState.bedroommirror);

    bool keyFound = Scene::getKeyFound();

    if (mGameState.dialogueActive && IsKeyPressed(KEY_E)){
        mGameState.dialogueActive = false;
        mGameState.dialogueStep = 0;
        return;
    }

    if (IsKeyPressed(KEY_E) && !mGameState.dialogueActive){
        if (nearMirror){ // go to the clue3 scene
            mGameState.nextSceneID = 13; // TODO: CHANGE TO CLUE SCENE
            return;
        }
        if (nearHallwayDoor){ // can't leave unless clues are found
            if(keyFound){ // could now go to hallway bcuz saved
                mGameState.nextSceneID = 4; // go to hallway
                return;
            }
            else{
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "No, I need to get it";
                mGameState.dialogueStep = 0;
                return;
            }
        }
        if ((nearBed && !keyFound) || (nearDresser && !keyFound) || 
            (nearShelves && !keyFound) || (nearTable && !keyFound) ||
            (nearWardrobe && !keyFound)){ // finding the first polaroid
            mGameState.dialogueActive = true;
            mGameState.dialogueText = "...";
            mGameState.dialogueStep = 0;
            return;
        }

    }

    // TODO: Add interaction stuff
    // TODO: Fix dialogue system so no double clicks
}

void Bedroom::render()
{
    ClearBackground(BLACK);

    // TODO: ADD CAMERA THINGS? more to like zoom into that room instead of void
    mGameState.bg->render();
    // mGameState.bg->displayCollider();
    mGameState.bedroombed->render();
    // mGameState.bedroombed->displayCollider();
    mGameState.bedroomdresser->render();
    // mGameState.bedroomdresser->displayCollider();
    mGameState.bedroomshelves->render();
    // mGameState.bedroomshelves->displayCollider();
    mGameState.bedroomtable->render();
    // mGameState.bedroomtable->displayCollider();
    mGameState.bedroomwardrobe->render();
    // mGameState.bedroomwardrobe->displayCollider();
    mGameState.bedroommirror->render();
    // mGameState.bedroommirror->displayCollider();
    mGameState.hallwaydoor->render();
    // mGameState.hallwaydoor->displayCollider();

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

    bool nearHallwayDoor = mGameState.player->isColliding(mGameState.hallwaydoor);
    bool nearBed = mGameState.player->isColliding(mGameState.bedroombed);
    bool nearDresser = mGameState.player->isColliding(mGameState.bedroomdresser);
    bool nearShelves = mGameState.player->isColliding(mGameState.bedroomshelves);
    bool nearTable = mGameState.player->isColliding(mGameState.bedroomtable);
    bool nearWardrobe = mGameState.player->isColliding(mGameState.bedroomwardrobe);
    bool nearMirror = mGameState.player->isColliding(mGameState.bedroommirror);

    if (nearHallwayDoor || (nearBed && !keyFound) || (nearDresser && !keyFound) || 
        (nearShelves && !keyFound) || (nearTable && !keyFound) || (nearWardrobe && !keyFound) 
        || nearMirror){
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

void Bedroom::shutdown()
{
    delete mGameState.bg;
    delete mGameState.player;
    delete mGameState.bedroombed;
    delete mGameState.bedroomdresser;
    delete mGameState.bedroomshelves;
    delete mGameState.bedroomtable;
    delete mGameState.bedroomwardrobe;
    delete mGameState.bedroommirror;
    delete mGameState.hallwaydoor;

    UnloadTexture(textureDialogueBox);
    // UnloadMusicStream(mGameState.bgm);
}
