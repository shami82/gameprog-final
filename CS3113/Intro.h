#include "Instruction.h"

#ifndef INTRO_H
#define INTRO_H

class Intro : public Scene
{
private:
    Texture2D textureDialogueBox;
    
public:
    Intro();
    Intro(Vector2 origin, const char *bgHexCode);
    ~Intro();

    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
