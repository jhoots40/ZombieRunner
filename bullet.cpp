#include "bullet.hpp"
#define PI 3.14159265


Bullet::Bullet(float x, float y, PC *pc, SDL_Renderer *renderer) : xVel_(0), yVel_(0)
{
    SDL_Surface *loadedSurface = IMG_Load("/Users/houtsjake/projectsCPP/zombie/sprites/bullet.png");
    if(loadedSurface == NULL)
        throw std::runtime_error("Failed to load surface for PC");
    
    bulletTexture_ = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(bulletTexture_ == NULL)
        throw std::runtime_error("Failed to load texture for PC");
    
    SDL_FreeSurface(loadedSurface);
    
    xPos_ = pc->getX();
    yPos_ = pc->getY();
    float xLocate = x - xPos_;
    float yLocate = -1 * (y - yPos_);
    angle_ = atan2(xLocate, yLocate);
    angle_ = angle_ - (90.0 * PI / 180);
    
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(bulletTexture_);
    bulletTexture_ = NULL;
}

void Bullet::move()
{
    xVel_ = 10 * cos(angle_);
    yVel_ = 10 * sin(angle_);
    xPos_ += xVel_;
    yPos_ += yVel_;
}

void Bullet::render(SDL_Renderer *renderer)
{
    SDL_Rect renderQuad = {xPos_, yPos_, 5, 12};
    SDL_RenderCopyEx(renderer, bulletTexture_, NULL, &renderQuad, 90 + angle_ * 180 / PI, NULL, SDL_FLIP_NONE);
}

bool Bullet::checkCollision(std::vector<Zombie *> &zombies)
{
    if(xPos_ + 5 > 1280 || xPos_ < 0 || yPos_ + 12 > 720 || yPos_ < 0)
        return true;
    
    for(int i = 0; i < zombies.size(); i++)
    {
        int zLeft = zombies.at(i)->zRect.x;
        int zRight = zombies.at(i)->zRect.x + zombies.at(i)->zRect.w;
        int zTop = zombies.at(i)->zRect.y;
        int zBottom = zombies.at(i)->zRect.y + zombies.at(i)->zRect.h;
        
        //if the tip of the bullet connects;
        int bLeft = xPos_;
        int bRight = xPos_ + 5;
        int bTop = yPos_;
        int bBottom = yPos_ + 3;
        
        if(bBottom <= zTop)
        {
            continue;
        }
        if(bTop >= zBottom)
        {
            continue;
        }
        if(bRight <= zLeft)
        {
            continue;
        }
        if (bLeft >= zRight)
        {
            continue;
        }
        
        zombies.at(i)->isAlive = false;
        return true;
        
    }
    return false;
}
