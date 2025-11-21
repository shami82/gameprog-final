#include "Scene.h"

bool Scene::completedpuz1 = false;
bool Scene::completedpuz2 = false;
bool Scene::completedpuz3 = false;

Scene::Scene() : mOrigin{{}} {}

Scene::Scene(Vector2 origin, const char *bgHexCode) : mOrigin{origin}, mBGColourHexCode {bgHexCode} 
{
    ClearBackground(ColorFromHex(bgHexCode));
}