#ifndef _GAME_H
#define _GAME_H

extern int DIMENSION = 15; //side length of the board

typedef struct tile {
	char value;
} tile_t;

typedef struct player {
	char* name;
	int score;
	tile_t* tiles;
	int numTiles; //up to 7 tiles at any time
} player_t;

typedef struct space {
	int row;
	int col;
	tile_t *tile; //pointer to tile, null if empty
	//int height; for when we do "Upwords"
} space_t;

typedef struct move {
	tile_t* tiles;
	int start; //index of start
	int end; //index of end
	int score;
} move_t;

typedef struct {
	player_t* players; //array of players (2-4)
	tile_t* tiles; //list of all tiles still "in the bag"
	board_t* board; //pointer to board
} game_t;

void init(int numPlayers);
void nextPlayer();
bool validMove(move_t* move);
void makeMove(player_t* player);
bool gameOver(); //return true if game is over

#endif 
