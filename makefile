FLAGS = -Wall -pedantic -o zombie
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCLUDE = -I /usr/local/Cellar/sdl2_image/2.0.5/include
LIB = -L /usr/local/Cellar/sdl2_image/2.0.5/lib
LIB_SDL_MAIN = -L /usr/local/Cellar/sdl2/2.0.14_1/lib/
FILES = main.cpp game.cpp pc.cpp background.cpp bullet.cpp zombie.cpp

BIN = zombie
RM = rm -f
ECHO = echo
OBJS = game.o

$(BIN):
	g++ $(FILES) $(INCLUDE) $(LIB) $(LIB_SDL_MAIN) $(FLAGS) $(LINKER_FLAGS)

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out