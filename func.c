#include "func.h"
#include <stdlib.h>

// Polygon
void polygon_init(Polygon *poly, int n){
	poly = (Polygon *) malloc(sizeof(Polygon));

	poly->numVertices = n;
	poly->numIndices = (n - 2) * 3;

	poly->vertices = (SDL_Vertex *) malloc(sizeof(SDL_Vertex));
	poly->indices = (int *) malloc(sizeof(int));
}

void polygon_destroy(Polygon *poly){
	free(poly->vertices);
	free(poly->indices);
	free(poly);
}
