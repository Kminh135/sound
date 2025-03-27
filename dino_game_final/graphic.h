#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "object.h"
#include <vector>

using namespace std;

bool loadAssets();
void renderBackground();
void renderDino();
void renderObstacle(const Obstacle &obs);
void renderText(const string& text, int x,int y);
void clearGraphics();

struct CactusInfo
{
    SDL_Texture* texture;
    int y,w,h;
};

extern vector<CactusInfo> cactusVariants;

extern SDL_Texture* birdFrame1;
extern SDL_Texture* birdFrame2;

#endif // GRAPHIC_H

