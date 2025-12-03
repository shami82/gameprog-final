#include "CS3113/ShaderProgram.h"

// Global Constants
constexpr int SCREEN_WIDTH     = 990,
              SCREEN_HEIGHT    = 720,
              FPS              = 120,
              NUMBER_OF_LEVELS = 16; // 5 rooms,1 start,1 instr,1 intro,2 end,3 memories,3 clues, 1 effect, 1 shader

constexpr Vector2 ORIGIN       = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
            
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

bool gIsTransitioning = false;
int gNextSceneIndex = -1;

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gLevels = {};

Start *gStart   = nullptr;
Instruction *gInstruction = nullptr;
Intro *gIntro = nullptr;
Attic *gAttic = nullptr;
Hallway *gHallway = nullptr;
HerRoom *gHerRoom = nullptr;
Clue1 *gClue1 = nullptr;
BadEnd *gBadEnd = nullptr;
Mem1 *gMem1 = nullptr;
LivingRoom *gLivingRoom = nullptr;
Clue2 *gClue2 = nullptr;
Mem2 *gMem2 = nullptr;
Bedroom *gBedroom = nullptr;
Clue3 *gClue3 = nullptr;
End *gEnd = nullptr;
Effects *gEffects = nullptr;
ShaderProgram gShader;
Vector2 gLightPosition = { 0.0f, 0.0f };


// Function Declarations
void switchToScene(Scene *scene);
void initialise();
void processInput();
void update();
void render();
void shutdown();

void switchToScene(Scene *scene)
{   
    gCurrentScene = scene;
    gCurrentScene->initialise();

    gEffects->start(FADEIN);
    gEffects->setEffectSpeed(1.5f);
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Still Here");
    InitAudioDevice();

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    gStart = new Start(ORIGIN, "#2D2A2A");
    gInstruction = new Instruction(ORIGIN, "#2D2A2A");
    gIntro = new Intro(ORIGIN, "#2D2A2A");
    gAttic = new Attic(ORIGIN, "#2D2A2A");
    gHallway = new Hallway(ORIGIN, "#2D2A2A");
    gHerRoom = new HerRoom(ORIGIN, "#2D2A2A");
    gClue1 = new Clue1(ORIGIN, "#2D2A2A");
    gBadEnd = new BadEnd(ORIGIN, "#2D2A2A");
    gMem1 = new Mem1(ORIGIN, "#2D2A2A");
    gLivingRoom = new LivingRoom(ORIGIN, "#2D2A2A");
    gClue2 = new Clue2(ORIGIN, "#2D2A2A");
    gMem2 = new Mem2(ORIGIN, "#2D2A2A");
    gBedroom = new Bedroom(ORIGIN, "#2D2A2A");
    gClue3 = new Clue3(ORIGIN, "#2D2A2A");
    gEnd = new End(ORIGIN, "#2D2A2A");

    gEffects = new Effects(ORIGIN, (float) SCREEN_WIDTH * 1.5f, (float) SCREEN_HEIGHT * 1.5f);

    gLevels.push_back(gStart);
    gLevels.push_back(gInstruction);
    gLevels.push_back(gIntro);
    gLevels.push_back(gAttic);
    gLevels.push_back(gHallway);
    gLevels.push_back(gHerRoom);
    gLevels.push_back(gClue1);
    gLevels.push_back(gBadEnd);
    gLevels.push_back(gMem1);
    gLevels.push_back(gLivingRoom);
    gLevels.push_back(gClue2);
    gLevels.push_back(gMem2);
    gLevels.push_back(gBedroom);
    gLevels.push_back(gClue3);
    gLevels.push_back(gEnd);

    switchToScene(gLevels[0]); // change to see specific scenes

    SetTargetFPS(FPS);
}

void processInput() 
{
    if(gCurrentScene != gLevels[0] && gCurrentScene != gLevels[1]
       && gCurrentScene != gLevels[2] && gCurrentScene != gLevels[6]
       && gCurrentScene != gLevels[7] && gCurrentScene != gLevels[8]
       && gCurrentScene != gLevels[10] && gCurrentScene != gLevels[11]
       && gCurrentScene != gLevels[13] && gCurrentScene != gLevels[14]){ // these dont have a player
        gCurrentScene->getState().player->resetMovement();

        Vector2 movement = gCurrentScene->getState().player->getMovement();
        if (movement.x > 0) gCurrentScene->getState().player->setDirection(RIGHT);
        else if (movement.x < 0) gCurrentScene->getState().player->setDirection(LEFT);
        else if (movement.y > 0) gCurrentScene->getState().player->setDirection(DOWN);
        else if (movement.y < 0) gCurrentScene->getState().player->setDirection(UP);

        if (IsKeyDown(KEY_A)) gCurrentScene->getState().player->moveLeft();
        if (IsKeyDown(KEY_D)) gCurrentScene->getState().player->moveRight();
        if (IsKeyDown(KEY_W)) gCurrentScene->getState().player->moveUp();
        if (IsKeyDown(KEY_S)) gCurrentScene->getState().player->moveDown();

        if (GetLength(gCurrentScene->getState().player->getMovement()) > 1.0f) 
            gCurrentScene->getState().player->normaliseMovement();
    }

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()){
        gAppStatus = TERMINATED;
    }

}

void update() 
{
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        Vector2 camTarget = gCurrentScene->getState().player ?
                    gCurrentScene->getState().player->getPosition() :
                    ORIGIN;
        gEffects->update(FIXED_TIMESTEP, &camTarget);
        gLightPosition = camTarget;
        gLightPosition = camTarget;
        gCurrentScene->update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    BeginDrawing();

    bool useEffect = gCurrentScene->usesFadeEffect();

    // use camera when level has camera
    if (gCurrentScene->getState().camera.target.x != 0 || gCurrentScene->getState().camera.target.y != 0){
        BeginMode2D(gCurrentScene->getState().camera);
        gCurrentScene->render();
        EndMode2D();
    } 

    else if (gCurrentScene == gLevels[3]){ // in the attic apply these shaders?
        Vector2 playerWorld = gCurrentScene->getState().player->getPosition();
        gShader.begin();
        gShader.setVector2("lightPosition", playerWorld);
        gCurrentScene->render();
        gShader.end();
    }

    else{
        gCurrentScene->render();
    }

    if (useEffect)
        gEffects->render();

    EndDrawing();
}

void shutdown() 
{
    delete gStart;
    delete gInstruction;
    delete gIntro;
    delete gAttic;
    delete gHallway;
    delete gHerRoom;
    delete gClue1;
    delete gBadEnd;
    delete gMem1;
    delete gLivingRoom;
    delete gClue2;
    delete gMem2;
    delete gBedroom;
    delete gClue3;
    delete gEnd;
    delete gEffects;

    for (int i = 0; i < NUMBER_OF_LEVELS; i++) gLevels[i] = nullptr;

    CloseAudioDevice();
    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();

        // now has fade out
        if (gCurrentScene->getState().nextSceneID >= 0 && !gIsTransitioning){
            gIsTransitioning = true;
            gNextSceneIndex = gCurrentScene->getState().nextSceneID;

            gEffects->start(FADEOUT);
            gEffects->setEffectSpeed(1.5f);
        }

        if (gIsTransitioning && gEffects->isFinished()){ // wait for fade then trasnition
            gIsTransitioning = false;
            switchToScene(gLevels[gNextSceneIndex]);
        }

        render();
    }

    shutdown();

    return 0;
}