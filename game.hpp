#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include "pc.hpp"
#include "background.hpp"
#include "bullet.hpp"
#include "zombie.hpp"

class Game
{
public:
    Game();
    ~Game();
    bool tick();
    void render();
    void renderLoseScreen();
    std::vector<Bullet *> bullets;
    std::vector<Zombie *> zombies;
private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    PC *pc_;
    Background *bg_;
    int frame_;
    SDL_Texture *loseScreenTexture_;
};

