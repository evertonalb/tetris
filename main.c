#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int SDL_main(int argc, char *args[]){
	SDL_Init(SDL_INIT_VIDEO);
	// Window
    const int width = 800;
    const int height = 800;
    SDL_Window *win = SDL_CreateWindow("Snake", width, height, SDL_WINDOW_MAXIMIZED);

	return 0;
}