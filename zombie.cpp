#include "zombie.hpp"
#define PI 3.14159265

Zombie::Zombie(float x, float y, PC *pc, SDL_Renderer *renderer) : isAlive(true), pc_(pc), xPos_(x), yPos_(y), xVel_(3), yVel_(0)
{
    zRect.x = xPos_;
    zRect.y = yPos_;
    zRect.w = 16;
    zRect.h = 32;
    
    SDL_Surface *loadedSurface = IMG_Load("/Users/houtsjake/projectsCPP/zombie/sprites/zombie.png");
    if(loadedSurface == NULL)
        throw std::runtime_error("Failed to load surface for zombie");
    
    zombieTexture_ = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(zombieTexture_ == NULL)
        throw std::runtime_error("Failed to load texture for zombie");
    
    SDL_FreeSurface(loadedSurface);
    
    for(int i = 0; i < 2; i++)
    {
        SDL_Rect rect = {i * 16, 0, 16, 32};
        zombieClips_.push_back(rect);
    }
}

Zombie::~Zombie()
{
    SDL_DestroyTexture(zombieTexture_);
    zombieTexture_ = NULL;
}

void Zombie::move()
{
    updateVelocity();
    xPos_ += xVel_;
    yPos_ += yVel_;
    zRect.x = xPos_;
    zRect.y = yPos_;
}

void Zombie::render(SDL_Renderer *renderer)
{
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    //SDL_RenderDrawRect(renderer, &zRect);
    SDL_Rect renderQuad = {xPos_, yPos_, 16, 32};
    SDL_RenderCopy(renderer, zombieTexture_, &zombieClips_.at(0), &renderQuad);
}

void Zombie::updateVelocity()
{
    float xLocate = pc_->getX() - xPos_;
    float yLocate = (pc_->getY() - yPos_);
    angle_ = atan2(xLocate, -1 * yLocate);
    angle_ = angle_ - (90.0 * PI / 180);
    //printf("%f\n", angle_ * 180 / PI);
    xVel_ = 3 * cos(angle_);
    yVel_ = 3 * sin(angle_);
}

bool Zombie::checkCollision()
{
    int zLeft = zRect.x;
    int zRight = zRect.x + zRect.w;
    int zTop = zRect.y;
    int zBottom = zRect.y + zRect.h;
    
    int pLeft = pc_->getX();
    int pRight = pc_->getX() + 16;
    int pTop = pc_->getY();
    int pBottom = pc_->getY() + 32;
    
    if(pBottom <= zTop)
    {
        return false;
    }
    if(pTop >= zBottom)
    {
        return false;
    }
    if(pRight <= zLeft)
    {
        return false;
    }
    if (pLeft >= zRight)
    {
        return false;
    }
    
    return true;
}


