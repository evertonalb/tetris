#include <SDL3/SDL.h>

// Polygon
typedef struct {
	int numVertices, numIndices;
	SDL_Vertex *vertices;
	int *indices;
} Polygon;

void polygon_init(Polygon *poly);

void polygon_destroy(Polygon *poly);
