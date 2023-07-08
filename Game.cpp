//
// Created by Konstantin on 17/06/2023.
//

#include "Game.h"
#include <ctime>
#include <iostream>
#include <chrono>
#include <cmath>

enum ParticleType{null,sand,water,wood,max};

Game::Game(int w,int h,int size):running(true),hand(sand),mouseDown(false),width(w),heigth(h) {
    window.Init("Physics",width,heigth);
    window.Clear();

    scale=size;
    std::vector<particle>tmp;
    for(int x=0;x<width/scale;++x){
        tmp.push_back(particle{null,false});
    }
    screen.resize(heigth/scale,tmp);

    sand_texture=window.LoadTexture("res/sand.png");
    water_texture=window.LoadTexture("res/water.png");
    wood_texture=window.LoadTexture("res/wood.png");
}

Game::~Game() {
    screen.clear();
}

bool Game::isRunning() const {
    return running;
}

void Game::Update() {
    auto event = Window::GetEvent();
    switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseDown=true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDown=false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym==SDLK_SPACE){
                hand++;
                if(hand==max)hand=null;
            }else if(event.key.keysym.sym==SDLK_ESCAPE)
                running=false;
    }

    if(mouseDown&&event.button.x>0&&event.button.x<width&&event.button.y>0&&event.button.y<heigth){
        int mx,my;
        SDL_GetMouseState(&mx,&my);
        screen[my/scale][mx/scale].id=hand;
    }

    for(int row=0;row<heigth/scale;++row){
        for(int x=0;x<width/scale;++x){
            if(screen[row][x].id!=null&&!screen[row][x].isModified){
                switch(screen[row][x].id){
                    case sand:
                        if(row+1>=heigth/scale)break;
                        
                        if(screen[row+1][x].id==null||screen[row+1][x].id==water){
                            int tmp=screen[row+1][x].id;
                            screen[row+1][x]=screen[row][x];
                            screen[row+1][x].isModified=true;
                            if(tmp==water){
                                screen[row][x].id=water;
                                break;
                            }
                            screen[row][x].id=null;
                        }else if(x+1<width/scale&&(screen[row+1][x+1].id==null||screen[row+1][x+1].id==water)){
                            int tmp=screen[row+1][x+1].id;
                            screen[row+1][x+1]=screen[row][x];
                            screen[row+1][x+1].isModified=true;
                            if(tmp==water){
                                screen[row][x].id=water;
                                break;
                            }
                            screen[row][x].id=null;
                        }else if(x-1>=0&&(screen[row+1][x-1].id==null||screen[row+1][x-1].id==water)){
                            int tmp=screen[row+1][x-1].id;
                            screen[row+1][x-1]=screen[row][x];
                            screen[row+1][x-1].isModified=true;
                            if(tmp==water){
                                screen[row][x].id=water;
                                break;
                            }
                            screen[row][x].id=null;
                        }
                        break;
                    case water:
                        if(row+1<heigth/scale&&screen[row+1][x].id==null){
                            screen[row+1][x]=screen[row][x];
                            screen[row+1][x].isModified=true;
                            screen[row][x].id=null;
                        }else if(row+1<heigth/scale&&x+1<screen[row].size()&&screen[row+1][x+1].id==null){
                            screen[row+1][x+1]=screen[row][x];
                            screen[row+1][x+1].isModified=true;
                            screen[row][x].id=null;
                        }else if(row+1<heigth/scale&&x-1>=0&&screen[row+1][x-1].id==null){
                            screen[row+1][x-1]=screen[row][x];
                            screen[row+1][x-1].isModified=true;
                            screen[row][x].id=null;
                        }else if(x+1<width/scale;screen[row][x+1].id==null){
                            screen[row][x+1]=screen[row][x];
                            screen[row][x+1].isModified=true;
                            screen[row][x].id=null;
                        }else if(x-1>=0;screen[row][x-1].id==null){
                            screen[row][x-1]=screen[row][x];
                            screen[row][x-1].isModified=true;
                            screen[row][x].id=null;
                        }
                        break;
                }
            }else if(screen[row][x].isModified){
                screen[row][x].isModified=false;
            }
        }
    }
}

void Game::Render() {
    window.Clear();

    for(int row=0;row<heigth/scale;++row){
        for(int x=0;x<width/scale;++x){
            if(screen[row][x].id==sand){
                window.DrawPoint(color{255,255,0,255},x*scale,row*scale,scale);
            }else if(screen[row][x].id==water){
                window.DrawPoint(color{0,0,255},x*scale,row*scale,scale);
            }else if(screen[row][x].id==wood){
                window.DrawPoint(color{139,69,19},x*scale,row*scale,scale);
            }
        }
    }

    SDL_Rect dst={0,0,75,75};
    switch(hand){
        case sand:
            window.DrawTexture(sand_texture,nullptr,&dst);
            break;
        case water:
            window.DrawTexture(water_texture,nullptr,&dst);
            break;
        case wood:
            window.DrawTexture(wood_texture,nullptr,&dst);
            break;
    }

    window.Present();
}