//
// Created by Konstantin on 17/06/2023.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#pragma once

#include "window.h"
#include <vector>

struct particle{
    int id;
    bool isModified;
};

class Game {
public:
    Game(int w,int h,int size);
    bool isRunning() const;
    virtual ~Game();
    void Update();
    void Render();
private:
    SDL_Texture* sand_texture;
    SDL_Texture* water_texture;
    SDL_Texture* wood_texture;
    bool running;
    Window window;
    std::vector<std::vector<particle>> screen;
    int hand;
    bool mouseDown;
    int scale;
    int width,heigth;
};


#endif //SNAKE_GAME_H
