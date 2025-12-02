#include "Clue2.h"

#ifndef MEM2_H
#define MEM2_H

class Mem2 : public Scene {
private:
    Texture2D textureBG;
    Texture2D textureMem1;
    Texture2D textureMem2;
    Texture2D textureMem3;
    Texture2D textureMem4;
    Texture2D textureMem5;
    Texture2D textureMem6;
    Texture2D textureMem7;
    Texture2D textureMem8;
    Texture2D textureMem9;
    Texture2D textureMem10;
    Texture2D textureMem11;
    Texture2D textureMem12;
    Texture2D textureDialogueBox;

    float flashTimer;
    bool flashing; // for the cool flash effect when showing 10-11
    bool flash10Shown;
    const float flashDuration = 0.5f; // time 10 stays on screen

public:

    Mem2();
    Mem2(Vector2 origin, const char *bgHexCode);
    ~Mem2();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif