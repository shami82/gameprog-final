#include "Bedroom.h"

#ifndef CLUE3_H
#define CLUE3_H

class Clue3 : public Scene {
private:
    Texture2D textureBG;
    Texture2D textureClue1;
    Texture2D textureClue2;
    Texture2D textureClue3;
    Texture2D textureClue4;
    Texture2D textureClue5;
    Texture2D textureClue6;
    Texture2D textureClue7;
    Texture2D textureClue8;
    Texture2D textureDialogueBox;

    bool minigameActive = false; // will be tru afterthe dialogue
    float minigameTimer = 0.0f; // checking how long has passed
    float fillAmount = 0.0f; // amount filled

    float minigameDuration = 15.0f; // seconds to attempt
    float fillTarget = 400.0f; // target fill amount
    float fillPerTap = 12.0f; // for every key press
    float drainPerSecond = 9.0f; // drain rate

    bool tappedOnce = false;
    bool showExitPrompt = false;

    float pulseTimer = 0.0f;
    float pulseSpeed = 8.0f;
    float pulseAmount = 0.06f;

    int triesLeft = 3; // for finding key
    // for the auto sequences
    bool autoSequenceRunning = false;
    float autoSeqTimer = 0.0f;
    int autoSeqIndex = 0;
    const float autoSeqStep = 0.5f;

public:

    Clue3();
    Clue3(Vector2 origin, const char *bgHexCode);
    ~Clue3();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;

private:
    bool isMouseInKeyRect() const;

};

#endif