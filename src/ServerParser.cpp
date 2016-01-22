#include "ServerParser.h"

#include <stdio.h>
#include <cstring>

ServerParser::ServerParser() {
  server_board_ = new ServerBoard();
}

bool ServerParser::ParseGetBoard(char* receive_buffer) {

  int words_count = 1;
  char *buffer_pointer = 0;

  //token contains command
  char command[TOKEN_SIZE];
  //token contains command status
  char command_status[TOKEN_SIZE];
  //temporary buffer
  char temp[TEMP_SIZE];

  strcpy(temp, receive_buffer);

  buffer_pointer = strtok(receive_buffer, DELIMITER);

  //write data into tokens
  while (buffer_pointer) {
    switch (words_count) {
      case 1:
        strcpy(command, buffer_pointer);
        words_count++;
        break;
      case 2:
        strcpy(command_status, buffer_pointer);
        words_count++;
        break;
    }
    buffer_pointer = strtok(0, DELIMITER);
  }
  // if command get_board is ok return true
  if (strcmp("get_board", command_status) == THE_SAME) {
    //place two tiles on the board
    server_board_->PlaceTile();
    server_board_->PlaceTile();
    ServerParserPrint();
    return true;
  } else {
    //return bad get_board status
    printf("bad\n");
    return false;
  }
  printf("\n");

  return true;
}

int ServerParser::ParseReceivedMove(char* receive_buffer) {

  int words_count = 1;
  char *buffer_pointer = 0;

  //token contains command
  char command[TOKEN_SIZE];
  //token contains command status
  char command_status[TOKEN_SIZE];
  //token contains move directory
  char directory[TOKEN_SIZE];
  //token contains directory status
  char directory_status[TOKEN_SIZE];
  //temporary buffer
  char temp[TEMP_SIZE];

  strcpy(temp, receive_buffer);

  buffer_pointer = strtok(receive_buffer, DELIMITER);

  //write data into tokens
  while (buffer_pointer) {
    switch (words_count) {
      case 1:
        strcpy(command, buffer_pointer);
        words_count++;
        break;
      case 2:
        strcpy(command_status, buffer_pointer);
        words_count++;
        break;
      case 3:
        strcpy(directory, buffer_pointer);
        words_count++;
        break;
      case 4:
        strcpy(directory_status, buffer_pointer);
        words_count++;
        break;
    }
    buffer_pointer = strtok(0, DELIMITER);
  }

  //if received command is up, make move UP and print it, return MOVE_OK
  if (strcmp("up", directory_status) == THE_SAME) {
    printf("move up\n");
    server_board_->Move(UP);
    server_board_->PlaceTile();
    ServerParserPrint();
    return MOVE_OK;
  }
  //if received command is down, make move DOWN and print it, MOVE_OK
  else if (strcmp("down", directory_status) == THE_SAME) {
    printf("move down\n");
    server_board_->Move(DOWN);
    server_board_->PlaceTile();
    ServerParserPrint();
    return MOVE_OK;
  }
  //if received command is right, make move RIGHT and print it, MOVE_OK
  else if (strcmp("right", directory_status) == THE_SAME) {
    printf("move right\n");
    server_board_->Move(RIGHT);
    server_board_->PlaceTile();
    ServerParserPrint();
    return MOVE_OK;
  }
  //if received command is left, make move LEFT and print it, MOVE_OK
  else if (strcmp("left", directory_status) == THE_SAME) {
    printf("move left\n");
    server_board_->Move(LEFT);
    server_board_->PlaceTile();
    ServerParserPrint();
    return MOVE_OK;
  }
  //if received command is new game, clear board anp place two tiles, NEW_GAME
  else if (strcmp("new_game", directory_status) == THE_SAME) {
    printf("new_game\n");
    server_board_->ClearBoard();
    server_board_->PlaceTile();
    server_board_->PlaceTile();
    ServerParserPrint();
    return NEW_GAME;
  } else if (strcmp("bad", directory_status) == THE_SAME) {
    //if received command is bad, move is bad, print it, return MOVE_BAD
    printf("bad move\n");
    server_board_->Move(BAD);
    ServerParserPrint();
    return MOVE_BAD;
    //if received command is exit or client disconnect - exit
  } else {
    return EXIT_GAME;
  }
  printf("\n");
  //by default
  return EXIT_GAME;
}

void ServerParser::ServerParserPrint() {
  server_board_->ServerPrint();
}
ServerParser::~ServerParser() {
  delete server_board_;
}
