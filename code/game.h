#ifndef _GAME_H
#define _GAME_H

typedef struct tile {
	char value;
} tile_t;

typedef struct player {
	char* name;
	int score;
	tile_t* tiles; //up to 7 tiles at any time
} player_t;

typedef struct board {
	int width;
	int length;
	//int height; for when we do "Upwords"
} board_t;

typedef struct {
	player_t* players; //array of players (2-4)
	tile_t* tiles; //list of all tiles still "in the bag"
	board_t* board; //pointer to board
} game_t;

//progress turn
void nextPlayer();

bool validMove();

void makeMove(player_t* player);