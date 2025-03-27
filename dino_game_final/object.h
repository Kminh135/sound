#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
const int JUMP_FORCE = -17;

enum DinoState
{
    DINO_IDLE, DINO_DUCK, DINO_GAMEOVER
};

struct Dino
{
    int x,y,w,h;
    int velocityY;
    bool isJumping;
    int state;
};

enum ObstacleType
{
    OBSTACLE_CACTUS, OBSTACLE_BIRD
};

struct Obstacle
{
    int x, y, w, h;
    SDL_Texture* textureCactus;
    SDL_Texture* textureBird1;
    SDL_Texture* textureBird2;
    ObstacleType type;
};


void updateDino(Dino& dino);
void updateObstacle(Obstacle& obstacle);
bool checkCollision(const Dino& dino, const Obstacle& obs);

#endif // OBJECT_H
