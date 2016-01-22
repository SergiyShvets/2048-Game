#include "ServerBoard.h"

#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <stdio.h>

ServerBoard::ServerBoard() {
  //false by default
  moved = false;
  placed = false;
  score = 0;

  // set time for rand() (every time drop different result)
  srand(static_cast<unsigned int>(time(NULL)));

  // set the board size 4x4
  board_.resize(BOARD_SIZE);
  for (int x = 0; x < BOARD_SIZE; x++) {
    board_[x].resize(BOARD_SIZE);
    for (int y = 0; y < BOARD_SIZE; y++) {
      board_[x][y].value;
    }
  }
}

void ServerBoard::PlaceTile() {
  //establish the possibility that the TWO value will fall 90% and 10%  FOUR
  short four_drop = 90;
  short divider = 100;

  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      if (!board_[x][y].value) {
        uint x0;
        uint y0;
        do {
          x0 = rand() % BOARD_SIZE;
          y0 = rand() % BOARD_SIZE;
        } while (board_[x0][y0].value);

        // calculate which value falls
        int result = rand() % divider;

        if (result > four_drop) {
          //if result more than 90 place value FOUR
          board_[x0][y0].value = FOUR_VAL;
        } else {
          //if result less than 90 place value TWO
          board_[x0][y0].value = TWO_VAL;
        }
        //check if tile is empty
        if (CheckMove())
          return;
      }
    }
  }
  //true if value placed successfully
  placed = true;
}

bool ServerBoard::CheckMove() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      //if tile is empty then returns true
      if (!board_[x][y].value)
        return true;
      else {
        if (CheckBounds(x + CELL, y, board_[x][y].value))
          return true;
        if (CheckBounds(x - CELL, y, board_[x][y].value))
          return true;
        if (CheckBounds(x, y + CELL, board_[x][y].value))
          return true;
        if (CheckBounds(x, y - CELL, board_[x][y].value))
          return true;
      }
    }
  }
  return false;
}

bool ServerBoard::CheckBounds(int x, int y, uint val) {
  //check bounds
  if (x < MIN_COORD || x > MAX_COORD || y < MIN_COORD || y > MAX_COORD)
    return false;
  return board_[x][y].value == val;
}

void ServerBoard::MoveVert(int x, int y, int cell) {

  //check if we can multiply two adjacent values which are moved vertically
  if (board_[x][y + cell].value
      && board_[x][y + cell].value == board_[x][y].value
      && !board_[x][y].blocked && !board_[x][y + cell].blocked) {
    //tile "from" which value was moved equal to zero (empty)
    board_[x][y].value = 0;
    //tile "to" value was moved multiply by two
    board_[x][y + cell].value *= MULTI;
    //count score of united tiles
    score += board_[x][y + cell].value;
    //if tile is blocked, we cant move value on this tile
    board_[x][y + cell].blocked = true;

    if (board_[x][y + cell].blocked != true)
      //if tile isnt blocked we can move
      moved = true;
  }
  //move value into empty tile vertically
  else if (!board_[x][y + cell].value && board_[x][y].value) {
    //move value horizontally
    board_[x][y + cell].value = board_[x][y].value;

    //tile moved "from" equal to zero (became empty)
    board_[x][y].value = 0;

    //true if successfully moved value
    moved = true;
  }
  //if cell is negative(-1) move UP, if cell is positive(+1) move DOWN
  if (cell > 0) {
    if (y + cell < MAX_COORD)
      MoveVert(x, y + cell, CELL);
  } else {
    if (y + cell > MIN_COORD)
      MoveVert(x, y + cell, -CELL);
  }
}

void ServerBoard::MoveHor(int x, int y, int cell) {

  //check if we can multiply two adjacent values which are moved horizontally
  if (board_[x + cell][y].value
      && board_[x + cell][y].value == board_[x][y].value
      && !board_[x][y].blocked && !board_[x + cell][y].blocked) {
    //tile "from" which value was moved equal to zero (empty)
    board_[x][y].value = 0;
    //tile "to" value was moved multiply by two
    board_[x + cell][y].value *= MULTI;
    //count score of united tiles
    score += board_[x + cell][y].value;
    //if tile is blocked, we cant move value on this tile
    board_[x + cell][y].blocked = true;

    if (board_[x + cell][y].blocked != true)
      //if tile isnt blocked we can move
      moved = true;
  }
  //move value into empty tile horizontally
  else if (!board_[x + cell][y].value && board_[x][y].value) {
    //move value horizontally
    board_[x + cell][y].value = board_[x][y].value;

    //tile moved "from" equal to zero (became empty)
    board_[x][y].value = 0;

    //true if successfully moved value
    moved = true;
  }
  //if cell is negative(-1) move LEFT, if cell is positive(+1) move RIGHT
  if (cell > 0) {
    if (x + cell < MAX_COORD)
      MoveHor(x + cell, y, CELL);
  } else {
    if (x + cell > MIN_COORD)
      MoveHor(x + cell, y, -CELL);
  }
}

void ServerBoard::Move(DIRECTION direction) {

  int v1 = 1;
  int v2 = 2;
  //unlock blocked tiles
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board_[x][y].blocked = false;
    }
  }
  switch (direction) {
    //moves all values up
    case UP:
      for (int x = 0; x < BOARD_SIZE; x++) {
        int y = v1;
        while (y < BOARD_SIZE) {
          if (board_[x][y].value)
            MoveVert(x, y, -CELL);
          y++;
        }
      }
      break;
      //moves all values down
    case DOWN:
      for (int x = 0; x < BOARD_SIZE; x++) {
        int y = v2;
        while (y >= 0) {
          if (board_[x][y].value)
            MoveVert(x, y, CELL);
          y--;
        }
      }
      break;
      //moves all values left
    case LEFT:
      for (int y = 0; y < BOARD_SIZE; y++) {
        int x = v1;
        while (x < BOARD_SIZE) {
          if (board_[x][y].value)
            MoveHor(x, y, -CELL);
          x++;
        }
      }
      break;
    case RIGHT:
      //moves all values right
      for (int y = 0; y < BOARD_SIZE; y++) {
        int x = v2;
        while (x >= 0) {
          if (board_[x][y].value)
            MoveHor(x, y, CELL);
          x--;
        }
      }
      break;
      //do nothing if move is bad
    default:
      direction = BAD;
      break;
  }
}

void ServerBoard::ServerPrint() {

  std::string game_status;
  //create file for the board data record
  FILE *server_out_file;
  server_out_file = fopen("ServerBoard.txt", "w");
  //check if file is open
  if (!server_out_file) {
     printf("Can't open ServerBoard.txt\n");
   }

  printf("\nScore: ");
  printf("%u\n", score);
  printf("     x0    x1    x2    x3  \n");
  printf("  =========================\n");

  for (int y = 0; y < BOARD_SIZE; y++) {
    printf("y%d", y);
    printf("| ");
    for (int x = 0; x < BOARD_SIZE; x++) {
      if (!board_[x][y].value)
        printf("   ");
      else {

        printf(" ");
        printf("%u", board_[x][y].value);
        printf(" ");
      }
      printf(" | ");

      //write coord to txt file them send to client (easily to reading than buffer) according with json format
      fprintf(
          server_out_file,
          "{\"value\":\"%d\",\"coord_x\":\"%d\",\"coord_y\":\"%d\",\"score\":\"%d\"} \n",
          board_[x][y].value, x, y, score);
    }
    printf("\n  =========================\n");
  }
  fclose(server_out_file);
  printf("\n");

}

void ServerBoard::ClearBoard() {
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      //clear board and score
      board_[x][y].value = 0;
      score = 0;
    }
  }
}

bool ServerBoard::GameOver()
{
  // if all tiles are blocked game over
  for (int y = 0; y < BOARD_SIZE; y++) {
      for (int x = 0; x < BOARD_SIZE; x++) {
       board_[x][y].blocked = false;
        return false;
      }
    }
  return true;
}
ServerBoard::~ServerBoard() {

}

