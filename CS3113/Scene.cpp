#include "Scene.h"

bool Scene::completedpuz1 = false;
bool Scene::completedpuz2 = false;
bool Scene::completedpuz3 = false;

// for the first puzzle
bool Scene::polaroid1Found = false;
bool Scene::polaroid2Found = false;
bool Scene::polaroid3Found = false;
bool Scene::polaroid4Found = false;

Scene::Scene() : mOrigin{{}} {}

Scene::Scene(Vector2 origin, const char *bgHexCode) : mOrigin{origin}, mBGColourHexCode {bgHexCode} 
{
    ClearBackground(ColorFromHex(bgHexCode));
}