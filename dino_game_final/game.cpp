#include "game.h"
#include "graphic.h"
#include "input.h"
#include "object.h"
#include "audio.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;
bool gameStarted = false;
bool gameOver = false;
bool paused = false;
int score = 0;
int highScore = 0;
int level = 1;
float gameSpeed = 0.5f;
float bgX = 0.0f;


Dino dino = {100, 250, 50, 50, 0, false, DINO_IDLE};
Obstacle obstacle = {0, 0, 0, 0, nullptr, nullptr, nullptr, OBSTACLE_CACTUS};

void loadHighScore()
{
    ifstream file("high_score.txt");
    if(file.is_open()){
        file >> highScore;
        file.close();
    }
    else{
        highScore = 0;
    }
}

void saveHighScore()
{
    ofstream file("high_score.txt");
    if(file.is_open()){
        file << highScore;
        file.close();
    }
}

bool initGame()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return false;
    if(IMG_Init(IMG_INIT_PNG) < 0) return false;
    if(TTF_Init() == -1) return false;

    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if( !window || !renderer) return false;

    srand(static_cast<unsigned int>(time(NULL)));

    if(!loadAssets()) return false;
    if(!loadAudio()) return false;
    loadHighScore();

    resetGame();

    return true;
}

void updateGame()
{
    if(gameStarted && !gameOver && !paused){
        playBackgroundMusic();
        bgX -= gameSpeed;

        if(bgX <= -SCREEN_WIDTH) bgX = 0.0f;

        updateDino(dino);
        updateObstacle(obstacle);
        if(checkCollision(dino,obstacle)){
            gameOver = true;
            dino.state = DINO_GAMEOVER;
            playGameOverSound();
            saveHighScore();
            stopBackgroundMusic();
            //if(score > highScore) highScore = score;
        }
        if(score > highScore){
            highScore = score;
        }
        int previousLevel = level;
        int newLevel = 1;
        while (score >= 10 * newLevel *(newLevel + 1) / 2){
            newLevel++;
        }
        level = newLevel;
        if(level > previousLevel) playLevelUpSound();
        gameSpeed = 5.0f + (level - 1) * 1.5f;
    }
}

void resetGame()
{
    gameOver = false;
    gameStarted = false;
    paused = false;
    score = 0;
    level = 1;
    gameSpeed = 5.0f;
    bgX = 0.0f;

    dino.x = 100;
    dino.y = 250;
    dino.w = 50;
    dino.h = 50;
    dino.velocityY = 0;
    dino.isJumping = false;
    dino.state = DINO_IDLE;

    int r = rand() % 2;
    if(r == 0){
        obstacle.type = OBSTACLE_CACTUS;
        int index = rand() % cactusVariants.size();
        obstacle.textureCactus = cactusVariants[index].texture;
        obstacle.textureBird1 = nullptr;
        obstacle.textureBird2 = nullptr;
        obstacle.y = cactusVariants[index].y;
        obstacle.w = cactusVariants[index].w;
        obstacle.h = cactusVariants[index].h;
        obstacle.x = SCREEN_WIDTH;
    }
    else{
        obstacle.type = OBSTACLE_BIRD;
        obstacle.textureCactus = nullptr;
        obstacle.textureBird1 = birdFrame1;
        obstacle.textureBird2 = birdFrame2;
        obstacle.w = 40;
        obstacle.h = 30;
        obstacle.x = SCREEN_WIDTH;

        int rr = rand() % 3;
        int base = 250 - rr * 25;
        obstacle.y = base;
    }
}

void renderGame()
{
    SDL_RenderClear(renderer);
    renderBackground();
    renderDino();
    renderObstacle(obstacle);

    renderText("Score: " + to_string(score), 600, 40);
    renderText("Level: " + to_string(level), 10, 10);
    renderText("High Score: " + to_string(highScore), 600, 10);

    if(!gameStarted){
        renderText("Press any key to start!", 250, 150);
        renderText("How to play", 325, 300);
        renderText("Press up-arrow or space to jump and press down-arrow to duck", 40, 330);
    }else if(gameOver){
        renderText("Game over!", 300,100);
        renderText("Press any key to restart",250,150);
    }else if(paused){
        renderText("Paused", 350, 150);
    }

    SDL_RenderPresent(renderer);
}

void cleanupGame()
{
    clearGraphics();
    cleanupAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
