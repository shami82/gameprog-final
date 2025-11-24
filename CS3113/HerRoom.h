#include "Hallway.h"

#ifndef HERROOM_H
#define HERROOM_H

class HerRoom : public Scene {
private:
    Texture2D textureBG;
    Texture2D texturePlayer;
    Texture2D textureDialogueBox;
    Texture2D textureHerBed;
    Texture2D textureBookshelf;
    Texture2D textureHerChair;
    Texture2D textureHerTable;
    Texture2D textureHerShelf;
    Texture2D textureHallwayDoor;
    Texture2D textureBeanbag;

    bool firstTimeDialoguePlayed = false;
    float dialogueDelayTimer = 0.0f;
    bool waitingForIntroDialogue = false;

public:

    HerRoom();
    HerRoom(Vector2 origin, const char *bgHexCode);
    ~HerRoom();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif