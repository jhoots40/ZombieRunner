#include "pc.hpp"
#include <stdexcept>
#include <math.h>

#define PI 3.14159265


PC::PC(SDL_Renderer *renderer) : xVel_(0), yVel_(0), d_(DOWN), up(false), down(false), left(false), right(false)
{
    xPos_ = (1280 - 16) / 2;
    yPos_ = (720 - 32) / 2;
    
    SDL_Surface *loadedSurface = IMG_Load("/Users/houtsjake/projectsCPP/zombie/sprites/pc.png");
    if(loadedSurface == NULL)
        throw std::runtime_error("Failed to load surface for PC");
    
    pcTexture_ = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(pcTexture_ == NULL)
        throw std::runtime_error("Failed to load texture for PC");
    
    SDL_FreeSurface(loadedSurface);
    
    for(int i = 0; i < SIZE; i++)
    {
        SDL_Rect rect = {i * 16, 0, 16, 32};
        spriteClips_.push_back(rect);
    }
}

PC::~PC()
{
    SDL_DestroyTexture(pcTexture_);
    pcTexture_ = NULL;
}

void PC::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: case SDLK_w:
                yVel_ -= 5;
                up = true;
                d_ = UP;
                break;
            case SDLK_DOWN: case SDLK_s:
                yVel_ += 5;
                down = true;
                d_ = DOWN;
                break;
            case SDLK_RIGHT: case SDLK_d:
                xVel_ += 5;
                right = true;
                d_ = RIGHT;
                break;
            case SDLK_LEFT: case SDLK_a:
                xVel_ -= 5;
                left = true;
                d_ = LEFT;
                break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: case SDLK_w:
                yVel_ = 0;
                up = false;
                break;
            case SDLK_DOWN: case SDLK_s:
                yVel_ = 0;
                down = false;
                break;
            case SDLK_RIGHT: case SDLK_d:
                xVel_ = 0;
                right = false;
                break;
            case SDLK_LEFT: case SDLK_a:
                xVel_ = 0;
                left = false;
                break;
        }
    }
}

void PC::render(SDL_Renderer *renderer, int frame)
{
    SDL_Rect renderQuad = {xPos_, yPos_, 16, 32};
    if(!isMoving())
    {
        SDL_RenderCopy(renderer, pcTexture_, &spriteClips_.at(d_), &renderQuad);
    }
    else
    {
        SDL_RenderCopy(renderer, pcTexture_, &spriteClips_.at(d_ + (frame / 6)), &renderQuad);
    }
}

void PC::move()
{
    updateVelocity();
    xPos_ += xVel_;
    if(xPos_ + 15 > 1280 || xPos_ < 0)
    {
        xPos_ -= xVel_;
    }
    
    yPos_ += yVel_;
    if(yPos_ + 32 > 720 || yPos_ < 0)
    {
        yPos_ -= yVel_;
    }
}

bool PC::isMoving()
{
    return up || down || left || right;
}

void PC::updateVelocity()
{
    if(down && right)
    {
        xVel_ = 5 * cos(45 * PI / 180.0);
        yVel_ = 5 * sin(45 * PI / 180.0);
        return;
    }
    if(down && left)
    {
        xVel_ = 5 * cos(45 * PI / 180.0) * (-1);
        yVel_ = 5 * sin(45 * PI / 180.0);
        return;
    }
    if(up && right)
    {
        xVel_ = 5 * cos(45 * PI / 180.0);
        yVel_ = 5 * sin(45 * PI / 180.0) * (-1);
        return;
    }
    if(up && left)
    {
        xVel_ = 5 * cos(45 * PI / 180.0) * (-1);
        yVel_ = 5 * sin(45 * PI / 180.0) * (-1);
        return;
    }
    if(right)
        xVel_ = 5;
    if(left)
        xVel_ = -5;
    if(up)
        yVel_ = -5;
    if(down)
        yVel_ = 5;
    
    return;
        
}

