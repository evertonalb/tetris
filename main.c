#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "func.h"

int SDL_main(int argc, char *args[]){
	SDL_Init(SDL_INIT_VIDEO);
	
	// Window
	const int margin = 50;
    const int width = 850;
    const int height = 800;
    SDL_Window *win = SDL_CreateWindow("Tetris", width, height, SDL_WINDOW_MAXIMIZED);	

	// Renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(win, NULL);

	// Grid
	SDL_FPoint *mainGrid[21];
	SDL_FPoint topLeft = {margin, margin};
	SDL_FPoint botLeft = {margin, height - margin};
	float cellSize = grid_init(20, 10, mainGrid, topLeft, botLeft);

	// Game loop
	SDL_Event event;
	bool running = true;
	while (running){
		// Event handling
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE){
					running = false;
				}
				break;
			case SDL_EVENT_QUIT:
				running = false;
				break;	
			default:
				break;
			}
		}

		// Drawing
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set background color to black
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set drawing color to white
		grid_draw(20, 10, mainGrid, renderer);

		SDL_RenderPresent(renderer);
	}

	grid_destroy(20, mainGrid);

	return 0;
}