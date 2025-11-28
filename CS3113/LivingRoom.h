#include "Mem1.h"

#ifndef LIVINGROOM_H
#define LIVINGROOM_H

class LivingRoom : public Scene {
private:
    Texture2D textureBG;
    Texture2D texturePlayer;
    Texture2D textureDialogueBox;
    Texture2D textureCouch1;
    Texture2D textureCouch2;
    Texture2D textureLivingBookShelf;
    Texture2D textureLivingShelf;
    Texture2D textureLivingStairs;
    Texture2D textureLivingStool;
    Texture2D textureLivingTable;
    Texture2D textureLivingTV;

    bool firstTimeDialoguePlayed = false;
    float dialogueDelayTimer = 0.0f;
    bool waitingForIntroDialogue = false;

    bool stoolActivated = false;
    int hidingSpot = -1;

public:

    LivingRoom();
    LivingRoom(Vector2 origin, const char *bgHexCode);
    ~LivingRoom();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif