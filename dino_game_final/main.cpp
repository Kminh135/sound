#include "game.h"
#include "input.h"

int main(int argc, char* argv[])
{

    if(!initGame()){
        return -1;
    }

    while(running){
        handleInput();
        updateGame();
        renderGame();
        SDL_Delay(16);
    }

    cleanupGame();
    return 0;
}
