#ifndef FUNC_H
#define FUNC_H

#include <SDL3/SDL.h>

// A right movement event would be EVENT_MOVEMENT + RIGHT and so on
#define EVENT_MOVEMENT 		 	  SDL_EVENT_USER
#define EVENT_FAST_FALL_ON	 	 (SDL_EVENT_USER + 1)
#define EVENT_FAST_FALL_OFF	 	 (SDL_EVENT_USER + 2)
#define EVENT_LOCK_TETROMINO 	 (SDL_EVENT_USER + 3)
#define EVENT_GAME_OVER		 	 (SDL_EVENT_USER + 4)
#define EVENT_ROTATE		 	 (SDL_EVENT_USER + 5)
#define EVENT_INSTANT_FALL	 	 (SDL_EVENT_USER + 6)
#define EVENT_CLEARING_ROW	 	 (SDL_EVENT_USER + 7)
#define EVENT_CLEARING_FINISHED	 (SDL_EVENT_USER + 8)

typedef struct {
	int i, j;
} Cell;

Cell new_cell(int i, int j);

// Returns a - b
Cell difference(Cell a, Cell b);

Cell add(Cell a, Cell b);

void rotate_cell(Cell *a, Cell reference);

// Tetromino
typedef enum {
	// One configuration
	O_TETROMINO,
	// Two rotations
	I_TETROMINO,
	S_TETROMINO,
	Z_TETROMINO,
	// Four rotations
	L_TETROMINO,
	J_TETROMINO,
	T_TETROMINO
} TetrominoType;

typedef struct {
	TetrominoType type;
	SDL_FColor color;
	unsigned short int currentRotation;
	unsigned short int maxRotations;
	Cell cells[4];
	int centerShift;
	Cell *rotationReference;
	int rotationIndex;
	int rotationLimit;
} Tetromino;

void get_tetromino(Tetromino *tetromino, TetrominoType type, SDL_FColor color);

void random_tetromino(Tetromino *tetromino);

bool is_cell_within_bounds(int rows, int cols, Cell cell);

bool is_tetromino_within_bounds(int rows, int cols, Tetromino tetromino);

typedef enum {RIGHT, LEFT, DOWN, UP} Direction;

bool move_tetromino(int rows, int cols, Tetromino *tetromino, Direction direction, bool *occupied[]);

void draw_tetromino(SDL_Renderer *renderer, Tetromino tetromino, int rows, int cols, SDL_FPoint *grid[rows]);

void rotate_tetromino(Tetromino *tetromino, int rows, int cols, bool *occupied[rows]);

// Draws a line
void draw_line(SDL_Renderer *renderer, SDL_FPoint start, SDL_FPoint end);

// Polygon
typedef struct {
	int numVertices, numIndices;
	SDL_Vertex *vertices;
	int *indices;
} Polygon;

void polygon_init(Polygon *poly, int n);

void polygon_destroy(Polygon *poly);

// Grid

// Returns cell size
float grid_init(int rows, int cols, SDL_FPoint *grid[rows+1], SDL_FPoint topLeft, SDL_FPoint botLeft);

void grid_destroy(int rows, SDL_FPoint *grid[rows + 1]);

void grid_draw(int rows, int cols, SDL_FPoint *grid[rows + 1], SDL_Renderer *renderer);

void fill_cell(int rows, int cols, SDL_FPoint *grid[rows + 1], int i, int j, SDL_Renderer *renderer, SDL_FColor color);

void on_key_press(SDL_KeyboardEvent keyboard);

void on_key_release(SDL_KeyboardEvent keyboard);

// Occupied cells boolean matrix

void bool_matrix_init(int rows, int cols, bool *arr[rows+1]);

void bool_matrix_destroy(int rows, bool *arr[rows]);

void lock(Tetromino tetromino, int rows, int cols, bool *occupied[rows]);

void draw_locked_tetrominoes(SDL_Renderer *renderer, int rows, int cols, bool *occupied[rows], SDL_FPoint *grid[rows+1]);

bool is_overlapping(Tetromino tetromino, int rows, int cols, bool *occupied[]);

void clear_rows(int rows, int cols, bool *occupied[rows], SDL_FPoint *grid[rows + 1], SDL_Renderer *renderer);

void clear_row(int i, int rows, int cols, bool *occupied[rows]);

#endif // FUNC_H