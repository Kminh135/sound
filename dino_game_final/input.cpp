#include "input.h"
#include "game.h"
#include "object.h"
#include "graphic.h"
#include "audio.h"
#include <SDL.h>

void confirmQuit()
{
    SDL_Event e;

    //SDL_RenderClear(renderer);
    renderText("Do you want to quit? ", 290, 180);
    renderText("y: Yes     n: No", 315, 210);
    SDL_RenderPresent(renderer);

    bool waiting = true;
    while(waiting){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_y){
                    running = false;
                    waiting = false;
                }
                else if(e.key.keysym.sym == SDLK_n){
                    waiting = false;
                }
            }
        }
        SDL_Delay(16);
    }
}

void handleInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) running = false;
        if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_ESCAPE){
                confirmQuit();
            }
            if(!gameStarted){
                gameStarted = true;
            }
            if(e.key.keysym.sym == SDLK_p){
                paused = !paused;
            }
            if((e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) &&
               !dino.isJumping && dino.state != DINO_DUCK && !gameOver && !paused){
                dino.isJumping = true;
                dino.velocityY = JUMP_FORCE;
                dino.state = DINO_IDLE;
                playJumpSound();
            }
            if(e.key.keysym.sym == SDLK_DOWN && !gameOver && !paused){
                dino.state = DINO_DUCK;
                dino.w = 100;
                dino.h = 25;
                dino.y = 275;
            }
            if(gameOver && e.type == SDL_KEYDOWN){
                resetGame();
            }
        }
        if(e.type == SDL_KEYUP){
            if(e.key.keysym.sym == SDLK_DOWN && !gameOver){
                dino.state = DINO_IDLE;
                dino.w = 50;
                dino.h = 50;
                dino.y = 250;
            }
        }
    }
}
