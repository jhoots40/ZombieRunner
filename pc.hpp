#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class PC
{
public:
    enum Direction {LEFT = 0, DOWN = 3, RIGHT = 6, UP = 9, SIZE = 12};
    PC(SDL_Renderer *renderer);
    ~PC();
    void render(SDL_Renderer *renderer, int frame);
    void handleEvent(SDL_Event &e);
    void move();
    bool isMoving();
    void updateVelocity();
    float getX() {return xPos_;}
    float getY() {return yPos_;}
private:
    SDL_Texture *pcTexture_;
    std::vector<SDL_Rect> spriteClips_;
    float xPos_, yPos_;
    float xVel_, yVel_;
    Direction d_;
    bool up, down, left, right;
};
