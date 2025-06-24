#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int SDL_main(int argc, char *args[]){
	SDL_Init(SDL_INIT_VIDEO);
	
	// Window
    const int width = 800;
    const int height = 600;
    SDL_Window *win = SDL_CreateWindow("Tetris", width, height, SDL_WINDOW_MAXIMIZED);

	SDL_Event event;
	bool running = true;
	while (running){
		// Event handling
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_EVENT_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
	}

	return 0;
}