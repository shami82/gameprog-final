#include "Intro.h"

#ifndef ATTIC_H
#define ATTIC_H

class Attic : public Scene {
private:
    Texture2D textureBG;
    Texture2D texturePlayer;
    Texture2D textureDialogueBox;
    Texture2D textureAtticDoor;
    Texture2D textureChest;
    Texture2D textureChestSolved;
    Texture2D textureWardrobe;
    Texture2D textureWardrobeSolved;
    Texture2D textureAlbum;
    Texture2D textureAlbumSolved;

    std::vector<Entity*> collidables;

    bool enteringCode = false;
    std::string currentCode = "";
    const std::string correctCode = "0812"; // first puzzle answer
    

public:

    Attic();
    Attic(Vector2 origin, const char *bgHexCode);
    ~Attic();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif