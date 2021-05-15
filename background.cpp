#include "background.hpp"
#include <stdexcept>
#include <time.h>

Background::Background(SDL_Renderer *renderer)
{
    SDL_Surface *loadedSurface = IMG_Load("/Users/houtsjake/projectsCPP/zombie/sprites/background.png");
    if(loadedSurface == NULL)
        throw std::runtime_error("Failed to load background surface");
    
    backgroundTexture_ = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(backgroundTexture_ == NULL)
        throw std::runtime_error("Failed to load background texture");
    
    SDL_FreeSurface(loadedSurface);
    
    srand(time(NULL));
    int count = 0;
    for(int y = 0; y < 45; y++)
    {
        for(int x = 0; x < 80; x++)
        {
            int x1, y1;
            while(1) {
                x1 = rand() % 4;
                y1 = rand() % 4;
                if(x1 == 3 && y1 == 1)
                {
                    if (count > 3)
                    {
                        count = 0;
                    }
                    else
                    {
                        count++;
                        continue;
                    }
                }
                break;
            }
            SDL_Rect rect = {16 * x1, 16 * y1, 16, 16};
            background[x][y] = rect;
        }
    }
    
}

Background::~Background()
{
    SDL_DestroyTexture(backgroundTexture_);
    backgroundTexture_ = NULL;
}

void Background::render(SDL_Renderer *renderer)
{
    for(int y = 0; y < 45; y++)
    {
        for(int x = 0; x < 80; x++)
        {
            SDL_Rect rect = {x * 16, y * 16, 16, 16};
            SDL_RenderCopy(renderer, backgroundTexture_, &background[x][y], &rect);
        }
    }
}
