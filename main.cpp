#include "CS3113/Clue2.h"

// Global Constants
constexpr int SCREEN_WIDTH     = 990,
              SCREEN_HEIGHT    = 720,
              FPS              = 120,
              NUMBER_OF_LEVELS = 11; // 5 rooms,1 start,1 instr,1 intro,2 end,3 memories,3 clues

constexpr Vector2 ORIGIN       = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
            
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

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
// Mem2 *gMem2 = nullptr;
// BedRoom *gBedRoom = nullptr;


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
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Still Here");
    InitAudioDevice();

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
    // gMem2 = new Mem2(ORIGIN, "#2D2A2A");
    // gBedRoom = new BedRoom(ORIGIN, "#2D2A2A");

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
    // gLevels.push_back(gMem2);
    // gLevels.push_back(gBedRoom);

    switchToScene(gLevels[0]);

    SetTargetFPS(FPS);
}

void processInput() 
{
    if(gCurrentScene != gLevels[0] && gCurrentScene != gLevels[1]
       && gCurrentScene != gLevels[2] && gCurrentScene != gLevels[6]
       && gCurrentScene != gLevels[7] && gCurrentScene != gLevels[8]
       && gCurrentScene != gLevels[10]){
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
        gCurrentScene->update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    BeginDrawing();

    // use camera when level has camera
    if (gCurrentScene->getState().camera.target.x != 0 || gCurrentScene->getState().camera.target.y != 0){
        BeginMode2D(gCurrentScene->getState().camera);
        gCurrentScene->render();
        EndMode2D();
    } 
    else{
        gCurrentScene->render();
    }

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
    // delete gMem2;
    // delete gBedRoom;

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

        if (gCurrentScene->getState().nextSceneID >= 0)
        {
            int id = gCurrentScene->getState().nextSceneID;
            switchToScene(gLevels[id]);
        }

        render();
    }

    shutdown();

    return 0;
}