#include <iostream>
#include "Game.h"
#include <iostream>

const int FPS=60;
const int FrameDelay=1000/FPS;

int main(int argc,char** argv){
    Game game=Game(600,600,8);

    int FrameStart;
    int FrameTime;

    while(game.isRunning()){
        FrameStart=SDL_GetTicks();

        game.Update();
        game.Render();
    
        FrameTime=SDL_GetTicks()-FrameStart;
        if(FrameDelay>FrameTime){
            SDL_Delay(FrameDelay-FrameTime);
        }
    }
    std::cout <<"Game over"<<std::endl;
    SDL_Delay(2000);
    return 0;
}