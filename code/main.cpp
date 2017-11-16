#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "refRenderer.h"
#include "cudaRenderer.h"
#include "game.h"

game* game;
player* players;
space* board;
tile* tiles;

// int DIMENSION = 15; //side length of the board

void createPlayers(int numPlayers) {
  players = (player *) malloc(numPlayers*sizeof(player));
  for(int i = 0; i < numPlayers-1; i++) {
    players[i].name = "Player "+std::to_string(i+1);
    players[i].score = 0;
    players[i].tiles = (tile *) malloc(7*sizeof(tile));
    players[i].numTiles = 0; //need to fill with 7
  }
  players[numPlayers-1].name = "Bot";
  players[numPlayers-1].score = 0;
  players[numPlayers-1].tiles = (tile *) malloc(7*sizeof(tile));
  players[numPlayers-1].numTiles = 0; //need to fill with 7
}

void free() {
  free(game);
  free(board);
  free(players);
}

int main(int argc, char** argv)
{
  createPlayers(3);
  board = (space *) calloc(DIMENSION*DIMENSION, sizeof(board));
  tiles = (tile *) malloc(NUMTILES * sizeof(tile));
  game->players = players;
  game->tiles = tiles;
  game->board = board;
  game->init(2);
  while(1) {
    game->makeMove(game->getCurrentPlayer());

    //TODO update GUI

    if(game->gameOver()) {
      return 0;
    }
  }
  return 0;
}
