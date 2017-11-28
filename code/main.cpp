#include <stdio.h>

// #include "refRenderer.h"
// #include "cudaRenderer.h"
#include "main.h"
#include "game.h"

player* createPlayers(int numPlayers) {
  player* players = (player *) malloc(numPlayers*sizeof(player));
  for(int i = 0; i < numPlayers-1; i++) {
    // players[i].name = "Player "+std::to_string(i+1);
    players[i].name = "Player";
    players[i].score = 0;
    players[i].tiles = (tile *) malloc(7*sizeof(tile));
    players[i].numTiles = 0; //need to fill with 7
  }
  players[numPlayers-1].name = "Bot";
  players[numPlayers-1].score = 0;
  players[numPlayers-1].tiles = (tile *) malloc(7*sizeof(tile));
  players[numPlayers-1].numTiles = 0; //need to fill with 7
  return players;
}

tile* createTiles() {
  tile* tiles = (tile *) malloc(NUMTILES*sizeof(tile));
	int tileIndex = 0;
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = ' '; //blank tile
		t.points = 0;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 9; i++) {
		tile t;
		t.letter = 'a';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'b';
		t.points = 3;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'c';
		t.points = 3;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'd';
		t.points = 2;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 12; i++) {
		tile t;
		t.letter = 'e';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'f';
		t.points = 4;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 3; i++) {
		tile t;
		t.letter = 'g';
		t.points = 2;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'h';
		t.points = 4;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 9; i++) {
		tile t;
		t.letter = 'i';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	tile t_j;
	t_j.letter = 'j';
	t_j.points = 8;
	tiles[tileIndex] = t_j;
	tileIndex++;
	tile t_k;
	t_k.letter = 'k';
	t_k.points = 5;
	tiles[tileIndex] = t_k;
	tileIndex++;
	for(int i = 0; i < 4; i++) {
		tile t;
		t.letter = 'l';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'm';
		t.points = 3;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 6; i++) {
		tile t;
		t.letter = 'n';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 8; i++) {
		tile t;
		t.letter = 'o';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'p';
		t.points = 3;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	tile t_q;
	t_q.letter = 'q';
	t_q.points = 10;
	tiles[tileIndex] = t_q;
	tileIndex++;
	for(int i = 0; i < 6; i++) {
		tile t;
		t.letter = 'r';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 4; i++) {
		tile t;
		t.letter = 's';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 6; i++) {
		tile t;
		t.letter = 't';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 4; i++) {
		tile t;
		t.letter = 'u';
		t.points = 1;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'v';
		t.points = 4;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'w';
		t.points = 4;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	tile t_x;
	t_x.letter = 'x';
	t_x.points = 8;
	tiles[tileIndex] = t_x;
	tileIndex++;
	for(int i = 0; i < 2; i++) {
		tile t;
		t.letter = 'y';
		t.points = 4;
		tiles[tileIndex] = t;
		tileIndex++;
	}
	tile t_z;
	t_z.letter = 'z';
	t_z.points = 10;
	tiles[tileIndex] = t_z;

	return tiles;
}

int main(int argc, char** argv)
{
  int numPlayers = 3; //TODO process input for number of players
  player* players = createPlayers(numPlayers); 
  tile* tiles = createTiles();
  space* board = (space *) calloc(DIMENSION*DIMENSION, sizeof(board));
  Game game(players, tiles, board);
  game.init();
  while(1) {
    game.makeMove(game.getCurrentPlayer());

    //TODO update GUI

    if(game.gameOver()) break;
    else game.nextPlayer();
  }
  
  //compute winner
  int maxScore = 0;
  player winner;
  for(int i = 0; i < numPlayers; i++) {
  	if(players[i].score > maxScore) {
  		winner = players[i];
  	}
  }

  //announce winner in GUI
  
  free(tiles);
  free(board);
  free(players);

  return 0;
}
