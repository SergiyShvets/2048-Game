#include "GameClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GameClient::GameClient() {
  client_socket_ = new Socket();
  client_packet_ = new Packet();
  client_parser_ = new ClientParser();
  //note that our buffers are Packet
  send_buffer_ = client_packet_->buffer;
  receive_buffer_ = client_packet_->buffer;
}

bool GameClient::StartConnection() {

  // start client and check socket functions
#ifdef WIN32
  if (!client_socket_->WsaInitialize()) {
    return false;
  }
#endif
  if (!client_socket_->CreateSocket()) {
    return false;
  }
  if (!client_socket_->ConnectSocket()) {
    return false;
  }
  //receive Server's message
  client_socket_->Receive(receive_buffer_);
  printf("%s\n", receive_buffer_);
  //start game
  StartClientGame();

  return true;
}

bool GameClient::StartClientGame() {

  bool game_over = false;
#ifdef WIN32
  system("cls");
#else
  system("clear");
#endif
  //send request to get board
  GetBoard();
  //false if command get board wanst successfull
 if(!GetBoardResponse(receive_buffer_))
   return false;
  BildBoard(receive_buffer_);
  //correct while !game over
   do {
    //make move
    MakeMove();
    MakeMoveResponse(receive_buffer_);
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
    GetBoardData(receive_buffer_);
    //print received data
    if(!BildBoard(receive_buffer_)){
      //game over
      game_over = true;
      printf("                                   Game Over!\n");
    }
  } while (!game_over);
  return true;
}


bool GameClient::GetBoard() {
  //send command get_board to the server
  sprintf(send_buffer_, "{\"command\": \"get_board\"}");
  client_socket_->Send(send_buffer_);
  return true;
}

bool GameClient::GetBoardResponse(char* receive_buffer){
  client_socket_->Receive(receive_buffer_);
   //parse resived response
   if (!client_parser_->ParseGetBoard(receive_buffer_))
     return false;
   return true;
}

void GameClient::GetBoardData(char* receive_buffer)
{
  client_socket_->Send("{\"command\":\"get_coords\", \"board\":\"ok\"}");
}
bool GameClient::ReceiveBoard(char* receive_buffer) {

  int data_count = 0;
  int max_count = 16;
  //open file for the record
  FILE *client_out_file;
  client_out_file = fopen("ClientBoard.txt", "w");
  //check if file is open
  if (!client_out_file) {
    printf("Can't open Text.txt");
    return false;
  }
  //receive a certain number of times so trash wasn't been received
  while (data_count < max_count) {
    client_socket_->Receive(receive_buffer);
    //write data string by string into file
    fprintf(client_out_file, "%s\n", receive_buffer);
    //quit from loop
    if (data_count == max_count)
      break;

    data_count++;
  }
  fclose(client_out_file);
  return true;
}

bool GameClient::BildBoard(char* receive_buffer) {

  int data_count = 0;
  int max_count = 16;

  ReceiveBoard(receive_buffer);
  //open file with board data
  FILE* client_in_file;
  client_in_file = fopen("ClientBoard.txt", "r");
  //check if file is open
  if (!client_in_file) {
    printf("Can't open Text.txt");
    return false;
  }
  while (data_count < max_count) {
    //read file data line by line
    while (fgets(receive_buffer, BUFF_SIZE, client_in_file))
      client_parser_->ParseReceivedBoard(receive_buffer);
    //quit from loop
    if (data_count == max_count)
      break;
    data_count++;
  }
  client_parser_->ClientParserPrint();
  fclose(client_in_file);
  return true;
}

void GameClient::MakeMove() {

  int pause = 1;
  int size = 10;
  char command[size];
  char move;

  printf("                                     [W]\n");
  printf(
      "                                 [A] [S] [D]\n                                      ");
  scanf(" %c", &move);
  switch (move) {
    case 'w':
    case 'W':
      // write into buffer command move UP
      sprintf(command, "up");
      break;
    case 's':
    case 'S':
      // write into buffer command move DOWN
      sprintf(command, "down");
      break;
    case 'd':
    case 'D':
      //  write into buffer command move RIGHT
      sprintf(command, "right");
      break;
    case 'a':
    case 'A':
      //  write into buffer command move LEFT
      sprintf(command, "left");
      break;
    case 'n':
    case 'N':
      //  write into buffer command NEW GAME
      sprintf(command, "new_game");
      break;
      // exit
    case 'e':
    case 'E':
      // clear all screen
      sprintf(command, "exit");
#ifdef WIN32
      system("cls");
#else
      system("clear");
#endif
      printf("\n\n\n                                  Good Bye!\n");
      sleep(pause);
      //remove created file
      remove("ClientBoard.txt");
      //close client socket
      client_socket_->CloseSocket();
      //exit from application
      exit(pause);
      break;
    default:
      //  write into buffer command BAD move
      sprintf(command, "bad");
      break;
  }
  // send buffer to server
  sprintf(send_buffer_,
          "{\"command\":\"make_move\",\"direction\":\"%s\",\"board\":\"ok\"}",
          command);
  client_socket_->Send(send_buffer_);
}

void GameClient::MakeMoveResponse(char* receive_buffer) {
  //receive move response
  client_socket_->Receive(receive_buffer_);
  client_parser_->ParseReceivedMove(receive_buffer_);
}

GameClient::~GameClient() {
  delete client_socket_;
  delete client_packet_;
  delete client_parser_;
}

