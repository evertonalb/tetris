#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "func.h"

int SDL_main(int argc, char *args[]){
	SDL_Init(SDL_INIT_VIDEO);
	
	// Window
	const int margin = 50;
    const int width = 450;
    const int height = 800;
    SDL_Window *win = SDL_CreateWindow("Tetris", width, height, SDL_WINDOW_MAXIMIZED);	

	// Renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(win, NULL);

	// Grid
	const int ROWS = 20, COLS = 10;
	SDL_FPoint *mainGrid[ROWS+1];
	SDL_FPoint topLeft = {margin, margin};
	SDL_FPoint botLeft = {margin, height - margin};
	float cellSize = grid_init(ROWS, COLS, mainGrid, topLeft, botLeft);

	// Occupied cells
	bool *occupied[ROWS];
	bool_matrix_init(ROWS, COLS, occupied);
	
	// Registering events
	SDL_RegisterEvents(6);
	
	// Time
	SDL_Time time, lastTime, clock = 0;
	
	// Setting the RNG seed
	SDL_GetCurrentTime(&time);
	SDL_srand(time);
	
	// Custom events
	SDL_Event customEvent;

	// Clearing
	Cell clearingQueue[COLS];
	SDL_FColor clearingColor = {0.5, 0.5, 0.5, 1.0};
	int clearingCount = 0;
	
	// First tetromino
	Tetromino currentTetromino;
	random_tetromino(&currentTetromino);

	for (int i = 0; i < currentTetromino.centerShift; i++)
		move_tetromino(ROWS, COLS, &currentTetromino, RIGHT, occupied);
	
	// Game loop
	SDL_GetCurrentTime(&lastTime);
	SDL_Event event;
	bool running = true, fastFall = false, instantFall = false, clearingRow = false;
	while (running){
		SDL_GetCurrentTime(&time);
		clock += time - lastTime;

		// Event handling
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_EVENT_KEY_DOWN:
				on_key_press(event.key);
				break;
			case SDL_EVENT_KEY_UP:
				on_key_release(event.key);
				break;
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case EVENT_MOVEMENT:
				SDL_UserEvent movementEvent = event.user;
				move_tetromino(ROWS, COLS, &currentTetromino, movementEvent.code, occupied);
				break;
			case EVENT_FAST_FALL_ON:
				fastFall = true;
				break;
			case EVENT_FAST_FALL_OFF:
				fastFall = false;
				break;
			case EVENT_LOCK_TETROMINO:
				lock(currentTetromino, ROWS, COLS, occupied);
				instantFall = false;
				random_tetromino(&currentTetromino);
				move_tetromino(ROWS, COLS, &currentTetromino, UP, occupied);
				move_tetromino(ROWS, COLS, &currentTetromino, UP, occupied);
				for (int i = 0; i < currentTetromino.centerShift; i++)
					move_tetromino(ROWS, COLS, &currentTetromino, RIGHT, occupied);
				break;
			case EVENT_GAME_OVER:
				running = false;
				break;
			case EVENT_ROTATE:
				rotate_tetromino(&currentTetromino, ROWS, COLS, occupied);
				break;
			case EVENT_INSTANT_FALL:
				instantFall = true;
				break;
			case EVENT_CLEARING_ROW:
				clearingRow = true;
				Cell c = {event.user.code, event.user.reserved};
				SDL_FColor grey = {0.5, 0.5, 0.5, 1.0};
				
				clearingQueue[clearingCount++] = c;
				
				occupied[c.i][c.j] = false;
				event.user.reserved++;
				if (event.user.reserved >= COLS) {
					event.user.type = EVENT_CLEARING_FINISHED;
					event.user.code = c.i;
				}

				SDL_PushEvent(&event);

				break;
			case EVENT_CLEARING_FINISHED:
				clearingCount = 0;
				clearingRow = false;
				clear_row(event.user.code, ROWS, COLS, occupied);
				clock = 0;
				break;
			default:
				break;
			}
		}

		if (!clearingRow) {
			// Gravity
			if (instantFall || clock > 500e6 || (fastFall && clock > 100e6) ){
				bool success;
				success = move_tetromino(ROWS, COLS, &currentTetromino, DOWN, occupied);
				if (!success){
					customEvent.type = EVENT_LOCK_TETROMINO;
					SDL_PushEvent(&customEvent);
				}
				clock = 0;
			}

			clear_rows(ROWS, COLS, occupied, mainGrid, renderer);
		}

		// Drawing
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set background color to black
		SDL_RenderClear(renderer);

		if (clearingRow){
			Cell c;
			for (int i = 0; i < clearingCount; i++){
				c = clearingQueue[i];
				fill_cell(ROWS, COLS, mainGrid, c.i, c.j, renderer, clearingColor);
			}
			SDL_Delay(50);
		}
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set drawing color to white
		
		grid_draw(ROWS, COLS, mainGrid, renderer);
		draw_tetromino(renderer, currentTetromino, ROWS, COLS, mainGrid);
		draw_locked_tetrominoes(renderer, ROWS, COLS, occupied, mainGrid);

		SDL_RenderPresent(renderer);

		lastTime = time;
	}

	grid_destroy(ROWS, mainGrid);
	bool_matrix_destroy(ROWS, occupied);

	return 0;
}