#include "func.h"
#include <stdlib.h>

Cell new_cell(int i, int j){
	Cell c = {i, j};
	return c;
}

Tetromino get_tetromino(TetrominoType type, SDL_FColor color){
	Tetromino tetromino;

	switch (type){
	case O_TETROMINO:
		tetromino.type = O_TETROMINO;

		tetromino.cells[0] = new_cell(0, 0);
		tetromino.cells[1] = new_cell(0, 1);
		tetromino.cells[2] = new_cell(1, 0);
		tetromino.cells[3] = new_cell(1, 1);

		tetromino.maxRotations = 0;

		break;
	case I_TETROMINO:
		tetromino.type = I_TETROMINO;

		tetromino.cells[0] = new_cell(2, 0);
		tetromino.cells[1] = new_cell(0, 0);
		tetromino.cells[2] = new_cell(1, 0);
		tetromino.cells[3] = new_cell(3, 0);

		tetromino.maxRotations = 2;

		break;
	case S_TETROMINO:
		tetromino.type = S_TETROMINO;

		tetromino.cells[0] = new_cell(0, 1);
		tetromino.cells[1] = new_cell(0, 2);
		tetromino.cells[2] = new_cell(1, 0);
		tetromino.cells[3] = new_cell(1, 1);

		tetromino.maxRotations = 2;

		break;
	case Z_TETROMINO:
		tetromino.type = Z_TETROMINO;

		tetromino.cells[0] = new_cell(0, 0);
		tetromino.cells[1] = new_cell(0, 1);
		tetromino.cells[2] = new_cell(1, 1);
		tetromino.cells[3] = new_cell(1, 2);

		tetromino.maxRotations = 2;

		break;
	case L_TETROMINO:
		tetromino.type = L_TETROMINO;
		tetromino.cells[0] = new_cell(0, 0);
		tetromino.cells[1] = new_cell(1, 0);
		tetromino.cells[2] = new_cell(2, 0);
		tetromino.cells[3] = new_cell(2, 1);

		tetromino.maxRotations = 4;

		break;
	case J_TETROMINO:
		tetromino.type = J_TETROMINO;
		tetromino.cells[0] = new_cell(0, 1);
		tetromino.cells[1] = new_cell(1, 1);
		tetromino.cells[2] = new_cell(2, 1);
		tetromino.cells[3] = new_cell(2, 0);

		tetromino.maxRotations = 4;

		break;
	case T_TETROMINO:
		tetromino.type = T_TETROMINO;
		tetromino.cells[0] = new_cell(0, 0);
		tetromino.cells[1] = new_cell(0, 1);
		tetromino.cells[2] = new_cell(0, 2);
		tetromino.cells[3] = new_cell(1, 1);

		tetromino.maxRotations = 4;

		break;
	}

	tetromino.currentRotation = 0;
	tetromino.color = color;

	return tetromino;
}

Tetromino random_tetromino(){

	int randomNumber = SDL_rand(7);

	SDL_FColor colors[] = {
		{1, 1, 0, 1},
		{0, 1, 1, 1},
		{0, 1, 0, 0},
		{1, 0, 0, 1},
		{1, 0.5, 0, 1},
		{0, 0, 1, 1},
		{1, 0, 0, 1}
	};

	return get_tetromino(randomNumber, colors[randomNumber]);
}

bool is_cell_within_bounds(int rows, int cols, Cell cell){
	int rowIsContained = (cell.i < rows && cell.i >= 0);
	int colIsContained = (cell.j < cols && cell.i >= 0);
	return (rowIsContained && colIsContained);
}

bool is_tetromino_within_bounds(int rows, int cols, Tetromino tetromino){
	for (int i = 0; i < 4; i++){
		if (!is_cell_within_bounds(rows, cols, tetromino.cells[i]))
			return false;
	}
	return true;
}

void move_tetromino(int rows, int cols, Tetromino *tetromino, Direction direction){
	int di = 0, dj = 0;

	Tetromino copy = *tetromino;

	switch (direction){
	case RIGHT:
		dj = 1;
		break;
	case LEFT:
		dj = -1;
		break;
	case DOWN:
		di = 1;
		break;
	}

	for (int i = 0; i < 4; i++){
		copy.cells[i].i += di;
		copy.cells[i].j += dj;
	}
	
	if (!is_tetromino_within_bounds(rows, cols, copy)) return;

	*tetromino = copy;
	
}

void draw_tetromino(SDL_Renderer *renderer, Tetromino tetromino, int rows, int cols, SDL_FPoint *grid[rows])
{
	for (int i = 0; i < 4; i++){
		Cell cur = tetromino.cells[i];
		fill_cell(rows, cols, grid, cur.i, cur.j, renderer, tetromino.color);
	}
}

void draw_line(SDL_Renderer *renderer, SDL_FPoint start, SDL_FPoint end) { SDL_RenderLine(renderer, start.x, start.y, end.x, end.y); }

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

void on_key_press(SDL_KeyboardEvent keyboard){

	SDL_Event customEvent;
	customEvent.type = SDL_EVENT_QUIT;
	
	switch (keyboard.key){
	case SDLK_ESCAPE:
		SDL_PushEvent(&customEvent);
		break;
	
	default:
		break;
	}
}

// Key presses