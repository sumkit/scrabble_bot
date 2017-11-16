#include "game.h"
#include <cstdio>

player* players;
int currPlayer;
space *board;
trieNode *roots; //size 26 array of roots for each letter in alphabet

// int DIMENSION = 15; //side length of the board

void makeTrie() {
	//setup file
	FILE *input = fopen("words.txt", "r");

  if (!input) {
    printf("Unable to open file: %s.\n", "words.txt");
    return;
  }

	//trie struct for all valid words
	roots = (trieNode *) malloc(26*sizeof(trieNode));
	for(char letter = 'a'; letter <= 'a'; letter++) {
		roots[letter-'a'].value = letter;
		roots[letter-'a'].nextLetters = (trieNode *) malloc(26*sizeof(trieNode));
	}

	//read file
  char *word;
  while (fscanf(input, "%s\n", word) != EOF) {
  	int index = 1;
  	trieNode curr = roots[word[0]-'a'];
  	while(word[index] != 0) {
  		if(curr.nextLetters[word[index]-'a'].value == 0) {
  			curr.nextLetters[word[index]-'a'].value = word[index]; 
  			curr.nextLetters[word[index]-'a'].nextLetters = (trieNode *) malloc(26*sizeof(trieNode));
  		}
  		curr = curr.nextLetters[word[index]-'a'];
  		index++;
  	}
  }
}

void init(int numPlayers) {
	players = (player *) malloc(numPlayers * sizeof(player));
}

void nextPlayer() {
	currPlayer++;
}

bool adjacentAbove(int row, int col) {
	space sp = board[row*DIMENSION + col];
	if(sp.tile != NULL) {
		if(sp.row == 0) return false;
		if(board[(row-1)*DIMENSION + col].tile == 0) return true;
	} 
	return false;
}
bool adjacentBelow(int row, int col) {
	space sp = board[row*DIMENSION + col];
	if(sp.tile != NULL) {
		if(sp.row == DIMENSION-1) return false;
		if(board[(row+1)*DIMENSION + col].tile == 0) return true;
	} 
	return false;
}
bool adjacentLeft(int row, int col) {
	space sp = board[row*DIMENSION + col];
	if(sp.tile != NULL) {
		if(sp.col == 0) return false;
		if(board[row*DIMENSION + col - 1].tile == 0) return true;
	} 
	return false;
}
bool adjacentRight(int row, int col) {
	space sp = board[row*DIMENSION + col];
	if(sp.tile != NULL) {
		if(sp.col == DIMENSION-1) return false;
		if(board[row*DIMENSION + col + 1].tile == 0) return true;
	} 
	return false;
}
bool validMove(move move) {
	return (move.start >= 0) && (move.end < DIMENSION);
}

//return best word surrounding a tile already on the board using the player's tiles
char* makeWord(char letter, tile *tiles) {
	char* best = NULL;
	player currPlayer = players[currPlayer];
	for(int i = 0; i < currPlayer.numTiles; i++) {	
	}
	return best;
}

move findBest() {
	player player = players[currPlayer];
	move best = {NULL, -1, -1, 0};
	for(int r = 0; r < DIMENSION; r++) { //row iteration
		//order from left to right
		int score = 0;
		for(int c = 0; c < DIMENSION; c++) { //col iteration
			int index = r*DIMENSION+c;
			tile *tile = board[index].tile;
			if(tile != NULL) {
				//look left and right of tile to form horizontal word
				if(adjacentLeft(r, c) && adjacentRight(r, c)) {
					makeWord(tile->value, player.tiles);
				}
			}
			//update best option
		}
	}
	for(int c = 0; c < DIMENSION; c++) {
		//order from top to bottom
		for(int r = 0; c < DIMENSION; r++) {
			int index = r*DIMENSION+c;
			tile *tile = board[index].tile;
			if(board[index].tile != NULL) {
				//look above and below of tile to form horizontal word
				if(adjacentAbove(r, c) && adjacentBelow(r, c)) {
					makeWord(tile->value, player.tiles);
				}
			}
			//update best option
		}
	}
	return best;
}

void makeMove(player* player) {
	move move;
	if(currPlayer == 3) {
		//bot's turn
		move = findBest();
	} else {
		//human's turn -> get input
		while(move.tiles == NULL || !validMove(move)) {
			//TODO show error for invalid moves
		}
	}

	//fill in board with move
	for(int i = move.start; i <= move.end; i++) {
		board[i].tile = &(move.tiles[i]);
	} 
}

bool gameOver() {
	return false;
}
