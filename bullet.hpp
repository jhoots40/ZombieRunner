#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <vector>
#include "pc.hpp"
#include "zombie.hpp"

class Bullet
{
public:
    Bullet(float x, float y, PC *pc, SDL_Renderer *renderer);
    ~Bullet();
    void move();
    void render(SDL_Renderer *renderer);
    bool checkCollision(std::vector<Zombie *> &zombies);
    SDL_Texture *getTexture() {return bulletTexture_;}
private:
    SDL_Texture *bulletTexture_;
    float xPos_, yPos_;
    float xVel_, yVel_;
    float angle_;
};
