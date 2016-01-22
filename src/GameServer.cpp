#include "GameServer.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

GameServer::GameServer(){
  server_socket_ = new Socket();
  server_packet_ = new Packet();
  server_parser_ = new ServerParser();
  //note that our buffers are Packet
  send_buffer_ = server_packet_->buffer;
  receive_buffer_ = server_packet_->buffer;
}

bool GameServer::StartServer() {

#ifdef WIN32
  system("cls");
#else
  system("clear");
#endif
  printf("Game Server Started:\n");

  // start server and check socket functions
#ifdef WIN32
  if (!server_socket_->WsaInitialize()) {
    return false;
  }
#endif

  if (!server_socket_->CreateSocket()) {
    return false;
  }

  if (!server_socket_->BindSocket()) {
    return false;
  }
  if (!server_socket_->ListenSocket()) {
    return false;
  }
  if (!server_socket_->AcceptSocket()) {
    return false;
  }
  //send message to client
  server_socket_->Send("Message from server: successfully connected\n");
  //start game
  StartServerGame();
  return true;
}

bool GameServer::StartServerGame() {

  bool is_connection = true;
  //response for client's request
  ResponseBoard();
  //send two tiles
  SendMove();
  //play game while client is connected
  do {
    //check move command
   if(!CheckMove())
     //quit condition
     is_connection = false;
   if(ReceiveGetData(receive_buffer_))
    //send move result with
    SendMove();
  }while (is_connection);

  return true;
}

//send move to client from file
bool GameServer::SendMove() {

  int data_count = 0;
  int max_count = 16;
  //open file with board data
  FILE* server_in_file;
  server_in_file = fopen("ServerBoard.txt", "r");
  //check if file is open
  if (!server_in_file) {
    printf("Can't open Text.txt\n");
    return false;
  }
  //send a certain number of times so trash wasn't been sent
  while (data_count < max_count) {

    while(fgets(send_buffer_, BUFF_SIZE,server_in_file))

      //send srting one by one from file to client
      server_socket_->Send(send_buffer_);

    //quit loop
    if (data_count == max_count)
      break;
    data_count++;
  }
  //close opened file
  fclose(server_in_file);
  return true;
}

bool GameServer::ResponseBoard() {

  server_socket_->Receive(receive_buffer_);

  //if command get_board is ok, place tile, print board and send response to client
  if (server_parser_->ParseGetBoard(receive_buffer_)) {
    sprintf(send_buffer_,
            "{ \"response\": \"get_board_response\", \"board:\" \"ok\"}");
    server_socket_->Send(send_buffer_);
  }
  // else send get_board was bad command
  else {
    sprintf(send_buffer_,
               "{ \"response\": \"get_board_response\", \"board:\" \"bad\"}");
    return false;
  }
  return true;
}

bool GameServer::ReceiveGetData(char* receive_buffer_){
  server_socket_->Receive(receive_buffer_);
  return true;
}
bool GameServer::CheckMove() {

  int pause = 1;

  server_socket_->Receive(receive_buffer_);

  if (server_parser_->ParseReceivedMove(receive_buffer_) == MOVE_OK) {
    //if parsed received move is ok send to client retribution ok
    sprintf(
        send_buffer_,
        "{\"response\":\"make_move\",\"status\":\"ok\"}");
    server_socket_->Send(send_buffer_);
    return true;
  } else if (server_parser_->ParseReceivedMove(receive_buffer_) == MOVE_BAD){
    //if parsed received move is bad send to client retribution bad
    sprintf(
        send_buffer_,
        "{\"responce\":\"make_move\",\"status\":\"bad\"}");
    server_socket_->Send(send_buffer_);
    return true;
  } else if (server_parser_->ParseReceivedMove(receive_buffer_) == NEW_GAME){
    //if parsed received move is bad send to client retribution bad
    sprintf(
        send_buffer_,
        "{\"responce\":\"make_move\",\"status\":\"new_game\"}");
    server_socket_->Send(send_buffer_);
    return true;
  } else /*if (server_parser_->ParseReceivedMove(receive_buffer_) == EXIT_GAME)*/{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("\n\n\n                              Client Disconnected!");
    printf("\n                                 Closing Server\n");
    sleep(pause);
    //remove created file
    remove("ServerBoard.txt");
    //close client socket
    server_socket_->CloseSocket();
    //exit from application
    exit(pause);
    return false;
  }
  return false;
}

GameServer::~GameServer() {
  delete server_socket_;
  delete server_packet_;
  delete server_parser_;
}
