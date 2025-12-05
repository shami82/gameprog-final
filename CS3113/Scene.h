#include "Entity.h"

#ifndef SCENE_H
#define SCENE_H

struct GameState
{
    Entity *player = nullptr;
    Entity *bg = nullptr; // needs unique collider offsets to the size of the walkable area (also used for title)
    
    Entity *dialoguebox = nullptr;
    bool dialogueActive = false;
    std::string dialogueText;
    int dialogueStep = 0; // for when there's multiple things of dialogue

    // for attic
    Entity *atticdoor = nullptr; // leads to the hallway
    Entity *chest = nullptr; // puzzle 1 interactable
    Entity *wardrobe = nullptr; // puzzle 2 interactable
    Entity *album = nullptr; // puzzle 3 interactable

    // for hallway
    Entity *atticstairs = nullptr; // leads back to attic
    Entity *herdoor = nullptr; // leads to herroom (puzzle 1)
    Entity *bedroomdoor = nullptr; // leads to bedroom (puzzle 3)
    Entity *livingroomdoor = nullptr; // leads to livingroom (puzzle 2)

    // for her room
    Entity *herbed = nullptr;
    Entity *herhallwaydoor = nullptr;
    Entity *beanbag = nullptr;
    Entity *herdesk = nullptr;
    Entity *herchair = nullptr;
    Entity *hershelf = nullptr;
    Entity *bookshelf = nullptr;
    Entity *hertable = nullptr;
    Entity *polaroids = nullptr;

    // for clues and memory scenes
    Entity *cutscene = nullptr;

    // for living room
    Entity *couch1 = nullptr;
    Entity *couch2 = nullptr;
    Entity *livingbookshelf = nullptr;
    Entity *livingshelf = nullptr;
    Entity *livingstairs = nullptr;
    Entity *livingstool = nullptr;
    Entity *livingtable = nullptr;
    Entity *livingtv = nullptr;

    // for bedroom
    Entity *bedroombed = nullptr;
    Entity *bedroomdresser = nullptr;
    Entity *bedroomshelves = nullptr;
    Entity *bedroomtable = nullptr;
    Entity *bedroomwardrobe = nullptr;
    Entity *bedroommirror = nullptr;
    Entity *hallwaydoor = nullptr;

    Music bgm = {0};
    Sound stairsSound = {0};
    Sound doorSound = {0};
    Music heartbeatLoop = {0};
    Sound sigh = {0};
    Sound ringing = {0};

    Camera2D camera = {0};

    int nextSceneID = -1;
};

class Scene 
{
protected: // similar to private but children and friend classes can use them
    GameState mGameState;
    Vector2 mOrigin;
    const char *mBGColourHexCode = "#2D2A2A";
    static bool completedpuz1;
    static bool completedpuz2;
    static bool completedpuz3;
    // for the first puzzle
    static bool polaroid1Found;
    static bool polaroid2Found;
    static bool polaroid3Found;
    static bool polaroid4Found;
    static bool seePolaroids;
    // for the second puzzle
    static bool picFound;
    static bool picPlaced;
    // for the third puzzle
    static bool keyFound;

public:
    Scene();
    Scene(Vector2 origin, const char *bgHexCode);

    virtual void initialise() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;

    static bool getPuz1Status()                 { return completedpuz1; }
    static void setPuz1Status(bool status)      { completedpuz1 = status; }
    static bool getPuz2Status()                 { return completedpuz2; }
    static void setPuz2Status(bool status)      { completedpuz2 = status; }
    static bool getPuz3Status()                 { return completedpuz3; }
    static void setPuz3Status(bool status)      { completedpuz3 = status; }

    // for puzzle 1
    static bool getPol1Status()                 { return polaroid1Found; }
    static void setPol1Status(bool status)      { polaroid1Found = status; }
    static bool getPol2Status()                 { return polaroid2Found; }
    static void setPol2Status(bool status)      { polaroid2Found = status; }
    static bool getPol3Status()                 { return polaroid3Found; }
    static void setPol3Status(bool status)      { polaroid3Found = status; }
    static bool getPol4Status()                 { return polaroid4Found; }
    static void setPol4Status(bool status)      { polaroid4Found = status; }
    static bool getSeePolaroids()               { return seePolaroids; }
    static void setSeePolaroids(bool status)    { seePolaroids = status; }
    
    // for puzzle 2
    static bool getPicFound()                   { return picFound; }
    static void setPicFoundStatus(bool status)  { picFound = status; }
    static bool getPicPlaced()                  { return picPlaced; }
    static void setPicPlacedStatus(bool status) { picPlaced = status; }

    // for puzzle 3
    static bool getKeyFound()                   { return keyFound; }
    static void setKeyFoundStatus(bool status)  { keyFound = status; }

    // for shaders
    virtual bool usesFadeEffect() const { return false; }

    virtual void renderScene() { render(); }
    virtual void renderDialogue() {}

    GameState   getState()           const { return mGameState; }
    Vector2     getOrigin()          const { return mOrigin;    }
    const char* getBGColourHexCode() const { return mBGColourHexCode; }

};

#endif