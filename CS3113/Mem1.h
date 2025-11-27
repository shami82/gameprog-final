#include "BadEnd.h"

#ifndef MEM1_H
#define MEM1_H

class Mem1 : public Scene {
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
    Texture2D textureDialogueBox;

    int currentIndex;
    float flashTimer;
    bool flashing; // for the cool flash effect when showing 8-10
    bool flash9Shown;
    const float flashDuration = 0.5f; // time 9 stays on screen

public:

    Mem1();
    Mem1(Vector2 origin, const char *bgHexCode);
    ~Mem1();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif