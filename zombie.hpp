#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pc.hpp"

class Zombie
{
public:
    Zombie(float x, float y, PC *pc, SDL_Renderer *renderer);
    ~Zombie();
    void move();
    void render(SDL_Renderer *renderer);
    SDL_Rect zRect;
    bool isAlive;
    float angle_;
    void updateVelocity();
    bool checkCollision();
private:
    PC *pc_;
    int xPos_, yPos_;
    int xVel_, yVel_;
    SDL_Texture *zombieTexture_;
    std::vector<SDL_Rect> zombieClips_;
};
