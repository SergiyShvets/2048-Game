#include "ClientBoard.h"

#include <stdio.h>

char empty[BOARD_SIZE] = "   ";

ClientBoard::ClientBoard() {

  score_ = "0";
  // set the board size 4x4
  board_.resize(BOARD_SIZE);
  for (int i = 0; i < BOARD_SIZE; i++) {
    board_[i].resize(BOARD_SIZE);
    for (int j = 0; j < BOARD_SIZE; j++) {
      //set all empty tiles empty status
      board_[i][j] = empty;
    }
  }
}

void ClientBoard::Client_Place(int x0, int y0, char* tile_value,
                               char* score_value) {
  //place tile value according to x y coordinates
  board_[x0][y0] = tile_value;
  score_ = score_value;
}

void ClientBoard::Client_Print() {
  //these large spaces are for a nice look in the middle of the application
  printf("\n                    Join the numbers and get to the 2048 tile!\n");
  printf("\n                          [N]ew Game    [E]xit Game \n");
  printf("\n                          Game 2048     Score: ");
  printf("%s\n\n", score_.c_str());
  printf("                          =========================\n");

  for (int y = 0; y < BOARD_SIZE; y++) {
    printf("                          | ");
    for (int x = 0; x < BOARD_SIZE; x++) {
      if (board_[x][y] == "0") {
        board_[x][y] = empty;
        printf("%s", empty);
      } else {
        printf(" ");
        printf("%s", board_[x][y].c_str());
        printf(" ");
      }
      printf(" | ");
    }
    printf("\n                          =========================\n");

  }
  printf("\n");
}

ClientBoard::~ClientBoard() {

}

