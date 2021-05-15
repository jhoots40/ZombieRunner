#include "game.hpp"
#include "background.hpp"
#include <stdexcept>
#include <time.h>
#include <unistd.h>

Game::Game() : frame_(0)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO");
    
    window_ = SDL_CreateWindow("Zombie Runner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    
    if(window_ == NULL)
        throw std::runtime_error("SDL_CreateWindow");
                                 
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(renderer_ == NULL)
        throw std::runtime_error("SDL_CreateRenderer");
    
    if(!IMG_Init(IMG_INIT_PNG))
        throw std::runtime_error("IMG_Init(IMG_INIT_PNG)");
    
    SDL_Surface *loadedSurface = IMG_Load("/Users/houtsjake/projectsCPP/zombie/sprites/losescreen.png");
    if(loadedSurface == NULL)
        throw std::runtime_error("Failed to load surface for PC");
    
    loseScreenTexture_ = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
    if(loseScreenTexture_ == NULL)
        throw std::runtime_error("Failed to load texture for PC");
    
    SDL_FreeSurface(loadedSurface);
    
    pc_ = new PC(renderer_);
    
    bg_ = new Background(renderer_);
    
    /*Zombie *z = new Zombie(16, 16, pc_, renderer_);
    zombies.push_back(z);*/
}

Game::~Game()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyTexture(loseScreenTexture_);
    window_ = NULL;
    renderer_ = NULL;
    loseScreenTexture_ = NULL;
    pc_->~PC();
    pc_ = NULL;
    bg_->~Background();
    bg_ = NULL;
    
    zombies.clear();
    bullets.clear();
    
    IMG_Quit();
    SDL_Quit();
}

bool Game::tick()
{
    bool quit = false;
    SDL_Event e;
    Uint32 timer = SDL_GetTicks();
    srand(time(NULL));
    while(!quit)
    {
        if(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                Bullet *b = new Bullet((float) x, (float) y, pc_, renderer_);
                bullets.push_back(b);
            }
            
            pc_->handleEvent(e);
        }
        if(SDL_GetTicks() - timer > 1000 && zombies.size() <= 30)
        {
            while(1)
            {
                int x = rand() % 1280;
                int y = rand() % 720;
                Zombie *z = new Zombie(x, y, pc_, renderer_);
                if(abs(pc_->getX() - x) < 150 || abs(pc_->getY() - y) < 150)
                {
                    zombies.push_back(z);
                    timer = SDL_GetTicks();
                    break;
                }
                z->~Zombie();
                z = NULL;
            }
        }
        for(int i = 0; i < bullets.size(); i++){
            bullets.at(i)->move();
        }
        
        for(int i = 0; i < zombies.size(); i++)
        {
            zombies.at(i)->move();
        }
        
        pc_->move();
        
        render();
        
        //erases bullets that collide or leave the screen
        for(int i = 0; i < bullets.size(); i++)
        {
            if(bullets.at(i)->checkCollision(zombies))
            {
                bullets.at(i)->~Bullet();
                bullets.erase(bullets.begin() + i);
            }
        }
        
        for(int i = 0; i < zombies.size(); i++)
        {
            if(zombies.at(i)->checkCollision())
            {
                quit = true;
            }

            
            if(zombies.at(i)->isAlive == false)
            {
                zombies.at(i)->~Zombie();
                zombies.erase(zombies.begin() + i);
            }
            
        }
        
        if(quit)
        {
            renderLoseScreen();
            usleep(3000000);
        }
    }
    return false;
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer_);
    
    bg_->render(renderer_);
    pc_->render(renderer_, frame_);
    for(int i = 0; i < zombies.size(); i++)
    {
        zombies.at(i)->render(renderer_);
    }
    for(int i = 0; i < bullets.size(); i++)
    {
        bullets.at(i)->render(renderer_);
    }
    
    SDL_RenderPresent(renderer_);
    
    frame_++;
    if(frame_ / 6 >= 3)
    {
        frame_ = 0;
    }
}

void Game::renderLoseScreen()
{
    SDL_Rect renderQuad = {0, 0, 1280, 720};
    SDL_RenderCopy(renderer_, loseScreenTexture_, NULL, &renderQuad);
    SDL_RenderPresent(renderer_);
}
