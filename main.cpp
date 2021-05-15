#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.hpp"

int main(int argc, char* argv[])
{
    Game game;
    while(game.tick());
    return 0;
}
