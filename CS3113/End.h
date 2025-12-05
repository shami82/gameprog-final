#include "Clue3.h"

#ifndef END_H
#define END_H

class End : public Scene {
private:
    Texture2D textureBG;
    Texture2D textureEnd1;
    Texture2D textureEnd2;
    Texture2D textureEnd3;
    Texture2D textureEnd4;
    Texture2D textureEnd5;
    Texture2D textureEnd6;
    Texture2D textureEnd7;
    Texture2D textureEnd8;
    Texture2D textureEnd9;
    Texture2D textureEnd10;
    Texture2D textureEnd11;
    Texture2D textureEnd12;
    Texture2D textureEnd13;
    Texture2D textureEnd14;
    Texture2D textureEnd15;
    Texture2D textureEnd16;
    Texture2D textureEnd17;
    Texture2D textureEnd18;
    Texture2D textureEnd19;
    Texture2D textureEnd20;
    Texture2D textureEnd21;
    Texture2D textureEnd22;
    Texture2D textureDialogueBox;

public:

    End();
    End(Vector2 origin, const char *bgHexCode);
    ~End();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif