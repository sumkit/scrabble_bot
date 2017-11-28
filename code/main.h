#include <stdlib.h>
#include <string>
#include <cstring>

const int DIMENSION = 15; //side length of the board
const int NUMTILES = 100;

#ifndef GAME_H
#define GAME_H

struct trieNode {
	char value;
	trieNode* nextLetters; //size 26 array
};

struct tile {
	char letter;
	int points;
};

struct player {
	char* name;
	int score;
	tile* tiles;
	int numTiles; //up to 7 tiles at any time
};

struct space {
	int row;
	int col;
	tile *spaceTile; //pointer to tile, null if empty
	//int height; for when we do "Upwords"
};

struct move {
	tile* tiles;
	int numTiles;
	int start; //index of start
	int end; //index of end
	int score;
};

#endif