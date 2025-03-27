#include "object.h"
#include "game.h"
#include "graphic.h"
#include <cstdlib>

using namespace std;

const int GRAVITY = 1;


void updateDino(Dino& dino)
{
    if(dino.isJumping && dino.state == DINO_DUCK){
        dino.isJumping = false;
        dino.y = 275;
    }
    if(dino.isJumping){
        dino.y += dino.velocityY;
        dino.velocityY += GRAVITY;
        if(dino.y >= 250)
        {
            dino.y = 250;
            dino.isJumping = false;
        }
    }
}

void updateObstacle(Obstacle& obstacle)
{
    obstacle.x -= gameSpeed;
    if(obstacle.x < -obstacle.w){
        score++;

        int r = rand() % 2;
        if(r == 0){
            obstacle.type = OBSTACLE_CACTUS;
            int index = rand() % cactusVariants.size();
            obstacle.textureCactus = cactusVariants[index].texture;
            obstacle.textureBird1 = nullptr;
            obstacle.textureBird2 = nullptr;
            obstacle.w = cactusVariants[index].w;
            obstacle.h = cactusVariants[index].h;
            obstacle.x = SCREEN_WIDTH;
            obstacle.y = cactusVariants[index].y;
        }
        else{
            if(gameOver) return;
            obstacle.type = OBSTACLE_BIRD;
            obstacle.textureCactus = nullptr;
            obstacle.textureBird1 = birdFrame1;
            obstacle.textureBird2 = birdFrame2;
            obstacle.w = 40;
            obstacle.h = 30;
            obstacle.x = SCREEN_WIDTH;
            int rr = rand() % 3;
            obstacle.y = 250 - rr*25;
        }
    }
}

bool checkCollision(const Dino& dino, const Obstacle& obs)
{
    return (dino.x < obs.x + obs.w && dino.x + dino.w > obs.x &&
            dino.y < obs.y + obs.h && dino.y + dino.h > obs.y);
}
