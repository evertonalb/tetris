#include "func.h"
#include <stdlib.h>

void draw_line(SDL_Renderer *renderer, SDL_FPoint start, SDL_FPoint end){ SDL_RenderLine(renderer, start.x, start.y, end.x, end.y); }

// Polygon
void polygon_init(Polygon *poly, int n){
	poly = (Polygon *) malloc(sizeof(Polygon));

	poly->numVertices = n;
	poly->numIndices  = (n - 2) * 3;

	poly->vertices = (SDL_Vertex *) malloc(sizeof(SDL_Vertex));
	poly->indices  = (int *) malloc(sizeof(int) * poly->numIndices);

	int vertex = 1;
	for (int i = 0; i < poly->numIndices; i += 3){
		poly->indices[i] 	= 0;
		poly->indices[i+1]	= vertex;
		poly->indices[i+2]	= ++vertex;
	}

}

void polygon_destroy(Polygon *poly){
	free(poly->vertices);
	free(poly->indices);
	free(poly);
}

// Grid
float grid_init(int rows, int cols, SDL_FPoint *grid[rows+1], SDL_FPoint topLeft, SDL_FPoint botLeft){
	float height = botLeft.y - topLeft.y;
	float cellSize = height / rows;

	SDL_FPoint pos = topLeft;
	// Column loop
	for (int i = 0; i <= rows; i++){
		grid[i] = (SDL_FPoint *) malloc(sizeof(SDL_FPoint) * (cols+1));
		// Row loop
		for (int j = 0; j <= cols; j++){
			grid[i][j] = pos;
			pos.x += cellSize;			
		}
		pos.x = topLeft.x;
		pos.y += cellSize;			
	}

	return cellSize;
}

void grid_destroy(int rows, SDL_FPoint *grid[rows + 1]){ for (int i = 0; i <= rows; i++) SDL_free(grid[i]); }

void grid_draw(int rows, int cols, SDL_FPoint *grid[rows + 1], SDL_Renderer *renderer){
	for (int i = 0; i <= rows; i++) draw_line(renderer, grid[i][0], grid[i][cols]); // horizontal lines
	for (int j = 0; j <= cols; j++) draw_line(renderer, grid[0][j], grid[rows][j]); // vertical lines
}

void fill_cell(int rows, int cols, SDL_FPoint *grid[rows + 1], int i, int j, SDL_Renderer *renderer, SDL_FColor color){
	SDL_Vertex vertices[4];

	SDL_FColor white = {1, 1, 1, 1};

	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;

	vertices[0].position = grid[i][j];
	vertices[1].position = grid[i+1][j];
	vertices[2].position = grid[i+1][j+1];
	vertices[3].position = grid[i][j+1];


	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);
}
