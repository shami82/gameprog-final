#include "Start.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction : public Scene {
private:
    Texture2D textureBG;

public:

    Instruction();
    Instruction(Vector2 origin, const char *bgHexCode);
    ~Instruction();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif