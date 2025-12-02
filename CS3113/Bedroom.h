#include "Mem2.h"

#ifndef BEDROOM_H
#define BEDROOM_H

class Bedroom : public Scene {
private:
    Texture2D textureBG;
    Texture2D texturePlayer;
    Texture2D textureDialogueBox;
    Texture2D textureBedroomBed;
    Texture2D textureBedroomDresser;
    Texture2D textureBedroomShelves;
    Texture2D textureBedroomTable;
    Texture2D textureBedroomWardrobe;
    Texture2D textureMirror;
    Texture2D textureHallwayDoor;

    std::vector<Entity*> collidables;

    bool firstTimeDialoguePlayed = false;
    float dialogueDelayTimer = 0.0f;
    bool waitingForIntroDialogue = false;

    bool mirrorInteracted = false;

public:

    Bedroom();
    Bedroom(Vector2 origin, const char *bgHexCode);
    ~Bedroom();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif