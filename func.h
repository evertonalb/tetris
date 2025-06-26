#include <SDL3/SDL.h>

typedef struct {
	int i, j;
} Cell;

// Tetromino
typedef enum {
	O_TETROMINO,
	I_TETROMINO,
	S_TETROMINO,
	Z_TETROMINO,
	L_TETROMINO,
	J_TETROMINO,
	T_TETROMINO
} TetrominoType;

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