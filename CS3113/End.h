#include "Clue3.h"

#ifndef END_H
#define END_H

class End : public Scene {
private:
    Texture2D textureBG;
    Texture2D textureEnd1;
    Texture2D textureEnd2;
    Texture2D textureEnd3;
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