#include "Clue1.h"

#ifndef BADEND_H
#define BADEND_H

class BadEnd : public Scene {
private:
    Texture2D textureBG;
    Texture2D textureBad1;
    Texture2D textureBad2;
    Texture2D textureBad3;
    Texture2D textureBad4;
    Texture2D textureBad5;
    Texture2D textureBad6;
    Texture2D textureDialogueBox;

public:

    BadEnd();
    BadEnd(Vector2 origin, const char *bgHexCode);
    ~BadEnd();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif