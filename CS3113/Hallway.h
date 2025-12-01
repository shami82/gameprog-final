#include "Attic.h"

#ifndef HALLWAY_H
#define HALLWAY_H

class Hallway : public Scene {
private:
    Texture2D textureBG;
    Texture2D texturePlayer;
    Texture2D textureDialogueBox;
    Texture2D textureAtticStairs;
    Texture2D textureHerDoor;
    Texture2D textureBedroomDoor;
    Texture2D textureLivingroomDoor;

    std::vector<Entity*> collidables;

public:

    Hallway();
    Hallway(Vector2 origin, const char *bgHexCode);
    ~Hallway();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif