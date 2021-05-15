#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Background
{
public:
    Background(SDL_Renderer *renderer);
    ~Background();
    void render(SDL_Renderer *renderer);
private:
    SDL_Texture *backgroundTexture_;
    std::vector<SDL_Rect> backgroundClips_;
    SDL_Rect background[80][45];
};
