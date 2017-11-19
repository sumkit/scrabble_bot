#ifndef _GAME_H
#define _GAME_H

#include <stdlib.h>
#include <string>
#include <cstring>

const int DIMENSION = 15; //side length of the board
const int NUMTILES = 100;

struct trieNode {
	char value;
	trieNode* nextLetters; //size 26 array
};

struct tile {
	char letter;
	int points;
};

struct player {
	std::string name;
	int score;
	tile* tiles;
	int numTiles; //up to 7 tiles at any time
};

struct space {
	int row;
	int col;
	tile *tile; //pointer to tile, null if empty
	//int height; for when we do "Upwords"
};

struct move {
	tile* tiles;
	int numTiles;
	int start; //index of start
	int end; //index of end
	int score;
};

struct game {
	player* players; //array of players (2-4)
	tile* tiles; //list of all tiles still "in the bag"
	space* board; //array of spaces to represent board
	void init();
	void makeMove(player* player);
	player *getCurrentPlayer();
	bool gameOver(); //return true if game is over
};

void makeMove(player *player);
void nextPlayer();

#endif
