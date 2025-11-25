#include "Entity.h"

#ifndef SCENE_H
#define SCENE_H

struct GameState
{
    Entity *player;
    Entity *bg; // needs unique collider offsets to the size of the walkable area (also used for title)
    
    Entity *dialoguebox;
    bool dialogueActive = false;
    std::string dialogueText;
    int dialogueStep = 0; // for when there's multiple things of dialogue

    // for attic
    Entity *atticdoor; // leads to the hallway
    Entity *chest; // puzzle 1 interactable
    Entity *wardrobe; // puzzle 2 interactable
    Entity *album; // puzzle 3 interactable

    // for hallway
    Entity *atticstairs; // leads back to attic
    Entity *herdoor; // leads to herroom (puzzle 1)
    Entity *bedroomdoor; // leads to bedroom (puzzle 3)
    Entity *livingroomdoor; // leads to livingroom (puzzle 2)

    // for her room
    Entity *herbed;
    Entity *herhallwaydoor;
    Entity *beanbag;
    Entity *herdesk;
    Entity *herchair;
    Entity *hershelf;
    Entity *bookshelf;
    Entity *hertable;
    Entity *polaroids;

    // for clues and memory scenes
    Entity *cutscene;

    // for living room
    Entity *couch1;
    Entity *couch2;
    Entity *livingbookshelf;
    Entity *livingshelf;
    Entity *livingstairs;
    Entity *livingstool;
    Entity *livingtable;
    Entity *livingtv;

    // for bedroom
    Entity *bedroombed;
    Entity *bedroomdresser;
    Entity *bedroomshelves;
    Entity *bedroomtable;
    Entity *bedroomwardrobe;
    Entity *bedroommirror;

    Music bgm;
    Sound stairsSound;
    Sound doorSound;

    Camera2D camera;

    int nextSceneID;
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
    
    GameState   getState()           const { return mGameState; }
    Vector2     getOrigin()          const { return mOrigin;    }
    const char* getBGColourHexCode() const { return mBGColourHexCode; }

};

#endif