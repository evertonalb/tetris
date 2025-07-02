#ifndef FUNC_H
#define FUNC_H

#include <SDL3/SDL.h>

// A right movement event would be EVENT_MOVEMENT + RIGHT and so on
#define EVENT_MOVEMENT SDL_EVENT_USER

typedef struct {
	int i, j;
} Cell;

Cell new_cell(int i, int j);

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
	Cell rotationReference;
} Tetromino;

Tetromino get_tetromino(TetrominoType type, SDL_FColor color);

Tetromino random_tetromino();

bool is_cell_within_bounds(int rows, int cols, Cell cell);

bool is_tetromino_within_bounds(int rows, int cols, Tetromino tetromino);

typedef enum {RIGHT, LEFT, DOWN} Direction;

void move_tetromino(int rows, int cols, Tetromino *tetromino, Direction direction);

void draw_tetromino(SDL_Renderer *renderer, Tetromino tetromino, int rows, int cols, SDL_FPoint *grid[rows]);

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

#endif // FUNC_H