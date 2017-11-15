#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string>

#include "refRenderer.h"
#include "cudaRenderer.h"
#include "game.h"

game_t* game;
player_t* players;
board_t* board;

void createPlayers(int numPlayers) {
  players = malloc(numPlayers*sizeof(player_t));
  for(int i = 0; i < numPlayers-1; i++) {
    player_t player = {"Player "+std::to_string(i+1), 0, (tile_t *) malloc(7*sizeof(tile_t))};
    players[i] = player;
  }
  player[numPlayers-1] = {"Bot", 0, (tile_t *) malloc(7*sizeof(tile_t))}; //bot
}

void free() {
  free(game);
  free(board);
  free(players);
}

int main(int argc, char** argv)
{
  createPlayers(3);
  board = (board_t *) calloc(DIMENSION*DIMENSION, sizeof(board_t));
  game = {players, tiles, board};
  while(1) {
    game.makeMove();

    //TODO update GUI

    if(game.gameOver()) {
      return 0;
    }
    game.nextPlayer();
  }
  return 0;
}
