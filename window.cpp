#include "window.h"

Window::~Window(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Window::Present() {
    SDL_RenderPresent(renderer);
}

void Window::Clear() {
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
}

SDL_Event Window::GetEvent(){
	SDL_Event event;
    SDL_PollEvent(&event);
    return event;
}

void Window::Init(const char* title,int w,int h) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    window= SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_SHOWN);
    renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}

void Window::DrawPoint(color c,int x,int y,int scale){
    SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,c.a);
    SDL_Rect dst={x,y,scale,scale};
    SDL_RenderFillRect(renderer,&dst);
}

void Window::DrawTexture(SDL_Texture* texture,SDL_Rect* src,SDL_Rect* dst){
    SDL_RenderCopy(renderer,texture,src,dst);
}

SDL_Texture* Window::LoadTexture(const char*filename){
    return IMG_LoadTexture(renderer,filename);
}