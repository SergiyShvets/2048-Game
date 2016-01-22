#include "ClientParser.h"

#include <stdio.h>
#include <unistd.h>
#include <cstring>

ClientParser::ClientParser()
{
  client_board_ = new ClientBoard();
}

bool ClientParser::ParseGetBoard(char* receive_buffer) {

  int words_count = 1;
  char *buffer_pointer = 0;

  // token contains response
  char response[TOKEN_SIZE];
  // token contains response
  char response_status[TOKEN_SIZE];
  // token contains response board
  char response_board[TOKEN_SIZE];
  // token contains  board status
  char board_status[TOKEN_SIZE];
  //temporary buffer
  char temp[TEMP_SIZE];

  strcpy(temp, receive_buffer);

  buffer_pointer = strtok(receive_buffer, DELIMITER);

  //write data into tokens
  while (buffer_pointer) {
    switch (words_count) {
      case 1:
        strcpy(response, buffer_pointer);
        words_count++;
        break;
      case 2:
        strcpy(response_status, buffer_pointer);
        words_count++;
        break;
      case 3:
        strcpy(response_board, buffer_pointer);
        words_count++;
        break;
      case 4:
        strcpy(board_status, buffer_pointer);
        words_count++;
        break;
    }
    buffer_pointer = strtok(0, DELIMITER);
  }

  //return true if response print_board is ok
  if (strcmp("ok", board_status) == THE_SAME) {
    return true;
  } else {
    //return true if response print_board is bad_board
    printf("bad_board\n");
    return false;
  }
  printf("\n");

  return true;
}

bool ClientParser::ParseReceivedMove(char* receive_buffer) {

  int words_count = 1;
  int pause = 1;
  char *buffer_pointer = 0;

  // token contains response
  char response[TOKEN_SIZE];
  // token contains response status
  char response_status[TOKEN_SIZE];
  // token contains retribution
  char retribution[TOKEN_SIZE];
  // token contains retribution status
  char retribution_status[TOKEN_SIZE];
  //temporary buffer
  char temp[TEMP_SIZE];

  strcpy(temp, receive_buffer);

  buffer_pointer = strtok(receive_buffer, DELIMITER);

  //write data into tokens
  while (buffer_pointer) {
    switch (words_count) {
      case 1:
        strcpy(response, buffer_pointer);
        words_count++;
        break;
      case 2:
        strcpy(response_status, buffer_pointer);
        words_count++;
        break;
      case 3:
        strcpy(retribution, buffer_pointer);
        words_count++;
        break;
      case 4:
        strcpy(retribution_status, buffer_pointer);
        words_count++;
        break;
    }
    buffer_pointer = strtok(0, DELIMITER);
  }

  // if retribution_status retribution is ok or new game return true, bad - false
  if (strcmp("ok", retribution_status) == THE_SAME) {
    return true;
  }
  else  if (strcmp("new_game", retribution_status) == THE_SAME) {
    printf("                                   New Game\n");
    sleep(pause);
    return true;
  }
  else {
    printf("                                  Wrong Key!\n");
    sleep(pause);
    return false;
  }
  printf("\n");
  return true;
}

bool ClientParser::ParseReceivedBoard(char* receive_buffer) {

  int words_count = 1;
  char *buffer_pointer = 0;
  int first_element = 0;

  // token contains value name
  char value_name[TOKEN_SIZE];
  // token contains value
  char tile_value[TOKEN_SIZE];
  // token contains coordinate_x name
  char coordinate_x[TOKEN_SIZE];
  // token contains x
  char x_value[TOKEN_SIZE];
  // token contains coordinate_y name
  char coordinate_y[TOKEN_SIZE];
  // token contains y
  char y_value[TOKEN_SIZE];
  // token contains score name
  char score_name[TOKEN_SIZE];
  // token contains score
  char score_value[TOKEN_SIZE];
  //temporary buffer
  char temp[TEMP_SIZE];

  strcpy(temp, receive_buffer);

  buffer_pointer = strtok(receive_buffer, DELIMITER);

  //write data into tokens
  while (buffer_pointer) {
    switch (words_count) {
      case 1:
        strcpy(value_name, buffer_pointer);
        words_count++;
        break;
      case 2:
        strcpy(tile_value, buffer_pointer);
        words_count++;
        break;
      case 3:
        strcpy(coordinate_x, buffer_pointer);
        words_count++;
        break;
      case 4:
        strcpy(x_value, buffer_pointer);
        words_count++;
        break;
      case 5:
        strcpy(coordinate_y, buffer_pointer);
        words_count++;
        break;
      case 6:
        strcpy(y_value, buffer_pointer);
        words_count++;
        break;
      case 7:
        strcpy(score_name, buffer_pointer);
        words_count++;
        break;
      case 8:
        strcpy(score_value, buffer_pointer);
        words_count++;
        break;
    }
    buffer_pointer = strtok(0, DELIMITER);
  }

  // convert char into int (x coordinate)
  int x = 0;
  if (x_value[first_element] == '0')
    x = 0;
  else if (x_value[first_element] == '1')
    x = 1;
  else if (x_value[first_element] == '2')
    x = 2;
  else if (x_value[first_element] == '3')
    x = 3;
  else {
    printf("error x\n");
    return false;
  }
  // convert char into int (y coordinate)
  int y = 0;
  y = y_value[first_element];
  if (y_value[first_element] == '0')
    y = 0;
  else if (y_value[first_element] == '1')
    y = 1;
  else if (y_value[first_element] == '2')
    y = 2;
  else if (y_value[first_element] == '3')
    y = 3;
  else {
    printf("error y\n");
    return false;
  }
  // substitute parsed data from buffer (coord x,coord y, value, score)
  client_board_->Client_Place(x, y, tile_value, score_value);

  return true;
}

void ClientParser::ClientParserPrint() {
  client_board_->Client_Print();
}

ClientParser::~ClientParser() {
  delete client_board_;
}
