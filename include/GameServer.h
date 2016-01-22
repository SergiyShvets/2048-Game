#ifndef GAMESERVER_H_
#define GAMESERVER_H_

#include "ServerParser.h"
#include "Socket.h"

class GameServer {
 public:
  GameServer();

  /**
   *@brief dtor free memory
   */
  ~GameServer();

  /**
   *@brief function starts server
   *@return true - successful, false - error
   */
  bool StartServer();

  /**
   *@brief function starts server game
   *@return true - successful, false - error
   */
  bool StartServerGame();

 private:
  /**
   *@brief function respond to client's board request
   *@return true - successful
   */
  bool ResponseBoard();

  /**
   *@brief function check clinet's move and sent back move status ok, bad or new game
   *@brief if clients command is exit - close socket and exit server
   *@return true - successful
   */
  bool CheckMove();

  /**
   *@brief function send to client coordinates and value of moved tile
   *@return true - successful
   */
  bool SendMove();

  /**
   *@brief function receive from client command get data
   *@return true - successful
   */
  bool ReceiveGetData(char* receive_buffer_);

  Socket *server_socket_;
  Packet *server_packet_;
  char *receive_buffer_;
  char *send_buffer_;
  ServerParser *server_parser_;

};

#endif
