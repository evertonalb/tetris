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
	const int ROWS = 20, COLS = 10;
	float cellSize = grid_init(ROWS, COLS, mainGrid, topLeft, botLeft);

	// Registering events
	SDL_RegisterEvents(1);

	// Time
	SDL_Time time, lastTime, delta;

	// Setting the RNG seed
	SDL_GetCurrentTime(&time);
	SDL_srand(time);

	// Game loop
	SDL_Event event;
	bool running = true;
	Tetromino currentTetromino = random_tetromino();
	SDL_GetCurrentTime(&lastTime);
	while (running){
		SDL_GetCurrentTime(&time);
		delta = time - lastTime;

		// Event handling
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_EVENT_KEY_DOWN:
				on_key_press(event.key);
				break;
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case EVENT_MOVEMENT:
				SDL_UserEvent movementEvent = event.user;
				move_tetromino(ROWS, COLS, &currentTetromino, movementEvent.code);
			default:
				break;
			}
		}

		// Drawing
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set background color to black
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set drawing color to white
		grid_draw(ROWS, COLS, mainGrid, renderer);
		draw_tetromino(renderer, currentTetromino, ROWS, COLS, mainGrid);

		SDL_RenderPresent(renderer);

		lastTime = time;
	}

	grid_destroy(ROWS, mainGrid);

	return 0;
}