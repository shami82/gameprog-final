#include "HerRoom.h"

#ifndef CLUE1_H
#define CLUE1_H

class Clue1 : public Scene {
private:
    Texture2D textureBG;
    Texture2D textureClue1Blur;
    Texture2D textureClue1Clear;
    Texture2D textureDialogueBox;

    bool minigameActive = false; // will be tru afterthe dialogue
    float minigameTimer = 0.0f; // checking how long has passed
    float fillAmount = 0.0f; // amount filled
    // int tapCount = 0; // how many taps were done (MIGHT REMOVE)

    float minigameDuration = 20.0f; // seconds to attempt
    float fillTarget = 400.0f; // target fill amount
    float fillPerTap = 12.0f; // for every key press
    float drainPerSecond = 5.0f; // drain rate
    // int maxTapsForAutoWin = 30; // MIGHT REMOVE depends on difficulty

    bool showExitPrompt = false;

public:

    Clue1();
    Clue1(Vector2 origin, const char *bgHexCode);
    ~Clue1();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif