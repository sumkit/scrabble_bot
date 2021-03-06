#include <cstdio>
#include <vector>
#include "main.h"
#include "game.h"

player* players; //array of players (2-4 including bot)
trieNode *roots; //size 26 array of roots for each letter in alphabet
int top, bottom, left, right; //bounding box of span of tiles
int currPlayer;
tile* gameTiles; //list of all tiles still "in the bag"
space* board; //array of spaces to represent board
int numPlayers;

Game::Game(player* p, tile *t, space *b, int num) {
	players = p;
	gameTiles = t;
	board = b;
	numPlayers = num;
}

void makeTrie() {
	//setup file
	FILE *input = fopen("words.txt", "r"); //valid words

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

void Game::init() {
	//guaranteed to be updated after player 1 makes move
	left = DIMENSION;
	right = -1;
	top = DIMENSION;
	bottom = -1;
	currPlayer = 0;
}
void Game::nextPlayer() {
	currPlayer++;
}
bool Game::validMove(move move) {
	return (move.start >= 0) && (move.end < DIMENSION);
}
bool validWord(std::string str) {
	//check in trie
	int index = 1;
	trieNode curr = roots[str.at(0) - 'a'];
	while(index < str.length()) {
		curr = curr.nextLetters[str.at(index)- 'a'];
		if(curr.value == 0) return false;
		index++;
	}
	return true;
}

void updateBoundingBox(move move) {
	//update bounding box of tiles on board
	int bestRowStart = move.start / DIMENSION;
	int bestColStart = move.start % DIMENSION;
	int bestRowEnd = move.end / DIMENSION;
	int bestColEnd = move.end % DIMENSION;
	left = (bestColStart < left) ? bestColStart : left;
	right = (bestColEnd > right) ? bestColEnd : right;
	top = (bestRowStart < top) ? bestRowStart : top;
	bottom = (bestRowEnd > bottom) ? bestRowEnd : bottom;
}

std::vector<std::string> permute(std::string str) {
	std::vector<std::string> v;
	v.insert(v.begin(), str);
	for(int index = 0; index < str.length(); index++) {
		for(int i = 0; i < str.length(); i++) {
			std::string temp;
			if(i < index) {
				temp = str.substr(0, i) + str.at(index) + str.substr(i, index) + str.substr(index+1, str.length());
			} else if(i > index) {
				temp = str.substr(0, index) + str.substr(index+1, i) + str.at(index) + str.substr(i+1, str.length());
			}
			//if i == index -> this is just the original string
			v.insert(v.end(), temp);
		}
	}
	return v;
}

player* Game::getCurrentPlayer() {return &(players[currPlayer]);}

/**
 * negative - amount in negative direction (left/up) of a board tile to check
 * positive - amount in positive direction (right/down) of a board tile to check
 */
std::vector<std::string> getPermutations(int length, int boardIndex, int negative, int positive) {
	tile* _tiles = players[currPlayer].tiles;
	int numTiles = players[currPlayer].numTiles;
	std::string str;
	for(int i = 0; i < numTiles; i++) {
		str+=_tiles[i].letter;
	}
	std::vector<std::string> v = permute(str);
	std::vector<std::string> res;
	for(int i = 0; i < v.size(); i++) {
		std::string temp = v[i].substr(0, length);
		//replace letters in temp with tiles on board
		for(int j = boardIndex-negative; j <= boardIndex+positive; j++) {
			if(board[j].spaceTile != NULL) {
				temp = temp.replace(boardIndex+positive-j, 1,
					std::string (1, board[j].spaceTile->letter), 0, 1);
			}
		}
		if(validWord(temp)) res.insert(res.end(), temp);
	}
	return res;
}

int calculateScore(move move) {
	int score = 0;
	tile *_tiles = move.tiles;
	int numTiles = move.numTiles;
	bool horizontal = (move.end - move.start == numTiles);
	for(int i = 0; i < numTiles; i++) {
		int thisPoints = _tiles[i].points;
		//check if special tile on board
		if(horizontal) {
			//if(board[move.start + i] == double word score)
		} else {}
		score += thisPoints;
	}
	return score;
}

move Game::findBest() {
	player player = players[currPlayer];
	move best = {NULL, 0, 0,0, 0};
	for(int r = left; r <= right; r++) { //row iteration
		int score = 0;
		for(int c = top; c <= bottom; c++) { //col iteration
			int index = r*DIMENSION+c;
			tile *tile = board[index].spaceTile;
			if(tile != NULL) {
				move temp;
				for(int l = 7; l >= 1; l--) {
					//look l above and l below tile
					std::vector<std::string> permutations = getPermutations(l, index, l, 7-l);
					std::vector<std::string> permutations2 = getPermutations(l, index, 7-l, l);
					permutations.insert(permutations.begin(), permutations2.begin(), permutations2.end());
					//find best valid word
					for(int z = 0; z < permutations.size(); z++) {
						std::string tempS = permutations.at(z);	

					}
				}
				//update best option
				if(best.score < calculateScore(temp)) {
					best = temp;
				}
			}
		}
	}
	for(int c = top; c <= bottom; c++) {
		for(int r = left; c <= right; r++) {
			int index = r*DIMENSION+c;
			tile *tile = board[index].spaceTile;
			if(tile != NULL) {
				move temp = {NULL, 0, -1, -1, 0};
				for(int l = 7; l >= 1; l--) {
					//look l left and l right of tile
					std::vector<std::string> permutations = getPermutations(l, index, l, 7-l);
					std::vector<std::string> permutations2 = getPermutations(l, index, 7-l, l);
					permutations.insert(permutations.begin(), permutations2.begin(), permutations2.end());
				}
				//update best option
				if(best.score < calculateScore(temp)) {
					best = temp;
				}
			}
		}
	}
	updateBoundingBox(best);
	return best;
}

void Game::makeMove(player* player) {
	move move;
	if(currPlayer == numPlayers-1) {
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
		board[i].spaceTile = &(move.tiles[i]);
	}
}

bool Game::gameOver() {
	return false;
}
