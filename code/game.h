#include <string>
#include <cstring>

class Game {
private:
	player* players; //array of players (2-4 including bot)
	trieNode *roots; //size 26 array of roots for each letter in alphabet
	int top, bottom, left, right; //bounding box of span of tiles
	int currPlayer;
	int numPlayers;
	tile* tiles; //list of all tiles still "in the bag"
	space* board; //array of spaces to represent board
public:
	Game(player* players, tile* tiles, space* board, int numPlayers);
	void init();
	void makeMove(player* player);
	player *getCurrentPlayer();
	bool gameOver(); //return true if game is over
	void nextPlayer();
	bool validMove(move move);
	move findBest();
};
