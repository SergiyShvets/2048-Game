#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include "ClientParser.h"
#include "Socket.h"

class GameClient {
 public:
  /**
   *@brief ctor initialize private objects
   */
  GameClient();

  /**
   *@brief dtor free memory
   */
  virtual ~GameClient();

  /**
   *@brief function starts client
   *@return true - successful, false - error
   */
  bool StartConnection();

  /**
   *@brief function starts client game
   *@return true - successful, false - error
   */
  bool StartClientGame();

  /**
   *@brief function have few option make move, request new game or exit
   *@brief and send option to the server
   *@return true - successful
   */
  void MakeMove();

 private:
  /**
   *@brief function send command  get board to server
   *@return true - successful
   */
  bool GetBoard();

  /**
   *@brief function received move get_board response
   *@param[receive_buffer] contains received data
   *@return true if get board is successful
   */
  bool GetBoardResponse(char* receive_buffer);

  /**
   *@brief function received board data from server
   *@param[receive_buffer] contains received data
   *@return true if all successful
   */
  bool ReceiveBoard(char* receive_buffer);

  /**
   *@brief function send command  get board data to server
   */
  void GetBoardData(char* receive_buffer);

  /**
   *@brief function build board from received data
   *@param[receive_buffer] contains received data
   *@return true if all is successful
   */
  bool BildBoard(char* receive_buffer);

  /**
   *@brief function received move response
   *@param[receive_buffer] contains received data
   */
  void MakeMoveResponse(char* receive_buffer);

  Socket *client_socket_;
  Packet *client_packet_;
  char *receive_buffer_;
  char *send_buffer_;
  ClientParser *client_parser_;
};

#endif
