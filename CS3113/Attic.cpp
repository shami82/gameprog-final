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
    textureChestSolved = LoadTexture("assets/attic/chest2.PNG");
    textureWardrobe = LoadTexture("assets/attic/wardrobe1.PNG");
    textureWardrobeSolved = LoadTexture("assets/attic/wardrobe2.PNG");
    textureAlbum = LoadTexture("assets/attic/album1.PNG");
    textureAlbumSolved = LoadTexture("assets/attic/album2.PNG");
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
        600.0f ,
        440.0f
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
        mGameState.player->getScale().x * 0.9f , // TODO: make little smaller?
        mGameState.player->getScale().y * 0.5f  // TODO: make little smaller?
    });
    mGameState.player->setColliderOffset({
        0.0f,
        mGameState.player->getScale().y * 0.25f // bottom half of the sprite
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

    if (Scene::getPuz2Status()){ // when returning to attic after completing puzzle2
        mGameState.wardrobe->setTexture(textureWardrobeSolved);
    }
    
    // ------------ CHEST -------------
    mGameState.chest = new Entity(
        {280.0f, 445.0f},
        {static_cast<float>(textureChest.width) * 0.8f,
         static_cast<float>(textureChest.height) * 0.8f},
        textureChest,
        NONE
    );
    mGameState.chest->setColliderDimensions({ 
        mGameState.chest->getScale().x + 10.0f, // little bigger?
        mGameState.chest->getScale().y + 10.0f
    });

    if (Scene::getPuz1Status()){ // when returning to attic after completing puzzle1
        mGameState.chest->setTexture(textureChestSolved);
    }
    
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

    if (Scene::getPuz3Status()){ // when returning to attic after completing puzzle3
        mGameState.album->setTexture(textureAlbumSolved);
    }
    
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

    collidables.clear();
    collidables.push_back(mGameState.wardrobe);
    collidables.push_back(mGameState.chest);
    collidables.push_back(mGameState.album);
    collidables.push_back(mGameState.atticdoor);

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
    // make a vector and pass that here for the vector of entities
    // mGameState.player->update(deltaTime, nullptr, nullptr, 0);
    mGameState.player->update(deltaTime,
                          mGameState.player,
                          collidables,
                          (int)collidables.size(),
                          mGameState.bg);
    if (IsKeyDown(KEY_A)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_D)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_W)) mGameState.player->animate(deltaTime);
    if (IsKeyDown(KEY_S)) mGameState.player->animate(deltaTime);

    nearChest = mGameState.player->isColliding(mGameState.chest);
    nearWardrobe = mGameState.player->isColliding(mGameState.wardrobe);
    nearAlbum = mGameState.player->isColliding(mGameState.album);
    bool nearAtticDoor = mGameState.player->isColliding(mGameState.atticdoor);

    // PUZZLE 1 LOGIC FOR ENTERIGN TEH COMBO
    if (enteringCode){ // entering the code
        int key = GetCharPressed(); // reading typed numbers
        while (key > 0){
            if (key >= '0' && key <= '9'){ // read only numbers
                if (currentCode.size() < 4)
                    currentCode.push_back((char)key);
            }

            key = GetCharPressed(); // read the next one
        }

        if (currentCode.size() == 4){ // submitting the code entered
            if (currentCode == correctCode){ // success condition
                Scene::setPuz1Status(true);
                mGameState.chest->setTexture(textureChestSolved);

                enteringCode = false;
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "it opened..";
                currentCode.clear();
                return;
            }
            else{ // fail condition
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "no, that's not it";
                enteringCode = false;
                currentCode.clear();
                return;
            }
        }

        return;
    }

    // PUZZLE 2 LOGIC FOR THE COMBO
    if (enteringCode2){
        int key = GetCharPressed();
        while (key > 0){
            if (key >= '0' && key <= '9'){
                if (currentCode2.size() < 4) currentCode2.push_back((char)key);
            }
            key = GetCharPressed();
        }

        if (currentCode2.size() == 4){
            if (currentCode2 == correctCode2){
                Scene::setPuz2Status(true);
                mGameState.wardrobe->setTexture(textureWardrobeSolved);

                enteringCode2 = false;
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "it opened...";
                currentCode2.clear();
                return;
            }
            else{
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "no, that's not it";
                enteringCode2 = false;
                currentCode2.clear();
                return;
            }
        }

        return;
    }

    if (mGameState.dialogueActive && IsKeyPressed(KEY_E)){ // special case for if it opened
        if (nearChest && mGameState.dialogueText == "it opened.."){
            mGameState.dialogueActive = false;
            mGameState.dialogueStep = 0;
            mGameState.nextSceneID = 8; // go to mem1
            return;
        }

        if (nearChest && !Scene::getPuz1Status() && mGameState.dialogueStep == 0){ // regular dialogue
            mGameState.dialogueStep = 1;
            mGameState.dialogueText = "I need to remember the combination...";
            return;
        }

        if (nearWardrobe && Scene::getPuz1Status() && !Scene::getPuz2Status()){ // wardrobe for combination
            if (mGameState.dialogueStep == 1){
                mGameState.dialogueStep = 2;
                mGameState.dialogueText = "I need to find the combination";
                return;
            }
        }

        if (nearWardrobe && mGameState.dialogueText == "it opened..."){
            mGameState.dialogueActive = false;
            mGameState.dialogueStep = 0;
            mGameState.nextSceneID = 11; // go to mem2
            return;
        }

        if (nearAlbum && mGameState.dialogueText == "it's open...") {
            mGameState.dialogueActive = false;
            mGameState.dialogueStep = 0;
            mGameState.nextSceneID = 14; // go to final memory
            return;
        }

        mGameState.dialogueActive = false;
        mGameState.dialogueStep = 0;
        return;
    }

    if (IsKeyPressed(KEY_E) && !mGameState.dialogueActive){
        if (nearAtticDoor){
            mGameState.nextSceneID = 4; // go to hallway
            return;
        }
        if (nearChest && !Scene::getPuz1Status()){ // puzzle 1 interaction
            if (IsKeyPressed(KEY_E) && !mGameState.dialogueActive){ // regular dialogue
                if (Scene::getPol1Status() && Scene::getPol2Status() 
                    && Scene::getPol3Status() && Scene::getPol4Status()){ // unlock combo login
                    enteringCode = true;
                    currentCode.clear();

                    mGameState.dialogueActive = true;
                    mGameState.dialogueText = "Enter the 4-digit combination:";
                }
                else{ // not all polaroids found
                    mGameState.dialogueActive = true;
                    mGameState.dialogueStep = 0;
                    mGameState.dialogueText = "It's locked";
                }

                return;
            }
        } 
        if (nearWardrobe){
            if (!Scene::getPuz1Status()){ // puz1 not done, cant do puz2
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "No... not yet";
                return;
            }

            if (Scene::getPicPlaced() && !Scene::getPuz2Status()){ // enter the combo for the wardrobe
                enteringCode2 = true;
                currentCode2.clear();
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "Enter the 4-digit combination:";
                return;
            }

            else if (Scene::getPuz1Status() && !Scene::getPuz2Status()){ // puz1 done, start puz2
                mGameState.dialogueActive = true;

                if (mGameState.dialogueStep == 0){ // first its locked
                    mGameState.dialogueText = "It's locked";
                    mGameState.dialogueStep = 1;
                    return;
                }

                else if (mGameState.dialogueStep == 1 && IsKeyPressed(KEY_E)){ // now need combo
                    mGameState.dialogueText = "I need to find the combination";
                    mGameState.dialogueStep = 2;
                    return;
                }
            }
        }
        if (nearAlbum){
            if (!Scene::getPuz2Status()){ // can't interact until puz2 done
                mGameState.dialogueActive = true;
                mGameState.dialogueText = "No... not yet";
                return;
            }
            else if (Scene::getPuz2Status() && !Scene::getKeyFound()){
                mGameState.dialogueActive = true;

                if (mGameState.dialogueStep == 0){ // first its locked
                    mGameState.dialogueText = "It's locked";
                    mGameState.dialogueStep = 1;
                    return;
                }

                else if (mGameState.dialogueStep == 1 && IsKeyPressed(KEY_E)){ // now need combo
                    mGameState.dialogueText = "I need the key...";
                    mGameState.dialogueStep = 2;
                    return;
                }
            }
            else{ // key was found
                mGameState.album->setTexture(textureAlbumSolved);
                mGameState.dialogueActive = true;
                mGameState.dialogueStep = 0;
                mGameState.dialogueText = "it's open...";
                return;
            }
        }
    }

    // TODO: Add interaction stuff with atticdoor, chest, wardrobe, and album
}

void Attic::renderScene()
{
    ClearBackground(BLACK);

    // TODO: ADD CAMERA THINGS? more to like zoom into that room instead of void
    mGameState.bg->render();
    // mGameState.bg->displayCollider();
    mGameState.wardrobe->render();
    // mGameState.wardrobe->displayCollider();
    mGameState.chest->render();
    // mGameState.chest->displayCollider();
    mGameState.album->render();
    // mGameState.album->displayCollider();
    mGameState.atticdoor->render();
    // mGameState.atticdoor->displayCollider();

    mGameState.player->render();
    // mGameState.player->displayCollider();
    
}

void Attic::renderDialogue(){
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

        if (enteringCode){ // for the combo login
            std::string display = currentCode;
            while (display.size() < 4)
                display.push_back('_'); // show the missing spots

            DrawText(
                display.c_str(),
                textX,
                textY + 40,
                32,
                WHITE
            );
        }

        if (enteringCode2){ // for the 2nd combo login
            std::string display2 = currentCode2;
            while (display2.size() < 4)
                display2.push_back('_'); // show the missing spots

            DrawText(
                display2.c_str(),
                textX,
                textY + 40,
                32,
                WHITE
            );
        }
    }

    nearChest = mGameState.player->isColliding(mGameState.chest);
    nearWardrobe = mGameState.player->isColliding(mGameState.wardrobe);
    nearAlbum = mGameState.player->isColliding(mGameState.album);
    bool nearAtticDoor = mGameState.player->isColliding(mGameState.atticdoor);

    // showing that you can interact with the corner text
    // TODO: FIX THIS SO IT DOESNT SHOW WHEN CHEST COMPLETE
    bool canInteract = (
        (nearChest && !getPuz1Status()) || (nearWardrobe && !getPuz2Status()) || nearAlbum || nearAtticDoor || 
        mGameState.dialogueActive
    );

    if (canInteract){
        const char* hint = "[E] to Interact";
        int fontSize = 20;

        int padding = 20;
        int textWidth = MeasureText(hint, fontSize);

        int drawX = GetScreenWidth() - textWidth - padding;
        int drawY = GetScreenHeight() - fontSize - padding;

        DrawText(hint, drawX, drawY, fontSize, WHITE);
    }
}

void Attic::render()
{
    renderScene();
    renderDialogue();
}

void Attic::shutdown()
{
    delete mGameState.bg;
    delete mGameState.player;
    delete mGameState.atticdoor;
    UnloadTexture(textureChest);
    UnloadTexture(textureChestSolved);
    UnloadTexture(textureWardrobe);
    UnloadTexture(textureWardrobeSolved);
    UnloadTexture(textureAlbum);
    UnloadTexture(textureAlbumSolved);
    UnloadTexture(textureDialogueBox);
    // UnloadMusicStream(mGameState.bgm);
}
