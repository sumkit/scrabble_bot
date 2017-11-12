#include "game.h"

player_t* players;
int currPlayer;
space_t *board;

void init(int numPlayers) {
	players = (player_t *) malloc(numPlayers * sizeof(player_t));
}

void nextPlayer() {
	currPlayer++;
}
player_t *getCurrentPlayer() {
	return &(players[currPlayer]);
}

bool adjacentAbove(int row, int col) {
	space_t space = board[row*DIMENSIONS + col];
	if(space -> tile != NULL) {
		if(space->row == 0) return false;
		if(board[(row-1)*DIMENSIONS + col] != NULL) return true;
	} 
	return false;
}
bool adjacentBelow(int row, int col) {
	if(space -> tile != NULL) {
		if(space->row == DIMENSIONS-1) return false;
		if(board[(row+1)*DIMENSIONS + col] != NULL) return true;
	} 
	return false;
}
bool adjacentLeft(int row, int col) {
	if(space -> tile != NULL) {
		if(space->col == 0) return false;
		if(board[row*DIMENSIONS + col - 1] != NULL) return true;
	} 
	return false;
}
bool adjacentRight(int row, int col) {
	if(space -> tile != NULL) {
		if(space->col == DIMENSIONS-1) return false;
		if(board[row*DIMENSIONS + col + 1] != NULL) return true;
	} 
	return false;
}
bool validMove(move_t* move) {
	return (move->start >= 0) && (move->end < DIMENSIONS);
}

//return best word surrounding a tile already on the board using the player's tiles
char* makeWord(char letter, tile_t *tiles) {
	char* best = NULL;
	player_t *currPlayer = players[currPlayer];
	for(int i = 0; i < currPlayer->numTiles; i++) {	
	}
	return best;
}

move_t* findBest() {
	player_t *player = players[currPlayer];
	move_t best = {NULL, -1, -1, 0};
	for(int r = 0; r < DIMENSIONS; r++) { //row iteration
		//order from left to right
		int score = 0;
		for(int c = 0; c < DIMENSIONS; c++) { //col iteration
			int index = r*DIMENSIONS+c;
			tile_t *tile = board[index].tile;
			if(tile != NULL) {
				//look left and right of tile to form horizontal word
				if(adjacentLeft(r, c) && adjacentRight(r, c)) {
					makeWord(tile->value, player->tiles);
				}
			}
			best = {NULL, r, c, score+= }; //update best option
		}
	}
	for(int c = 0; c < DIMENSIONS; c++) {
		//order from top to bottom
		for(int r = 0; c < DIMENSIONS; r++) {
			if(board[index].tile != NULL) {
				//look above and below of tile to form horizontal word
				if(adjacentAbove(r, c) && adjacentBelow(r, c)) {
					makeWord(tile->value, player->tiles);
				}
			}
		}
	}
	return &best;
}

void makeMove(player_t* player) {
	if(!validMove()) return;
	move_t *move;
	if() {
		//bot's turn
		move = findBest();
	} else {
		//human's turn -> get input
	}

	//fill in board with move
	for(int i = move.start; i <= move.end; i++) {
		board[i].tile = &(move.tiles[i]);
	} 
}
