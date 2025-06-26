#include <SDL3/SDL.h>

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
