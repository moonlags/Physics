#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct color{
	int r,g,b,a;
};

class Window{
public:
	void Init(const char* title,int w,int h);
	virtual ~Window();
	void Clear();
	static SDL_Event GetEvent();
    void Present();
    void DrawPoint(color c,int x,int y,int scale);
	SDL_Texture* LoadTexture(const char* filename);
	void DrawTexture(SDL_Texture* texture,SDL_Rect* src,SDL_Rect *dst);
private:
	SDL_Window* window=nullptr;
	SDL_Renderer* renderer=nullptr;
};