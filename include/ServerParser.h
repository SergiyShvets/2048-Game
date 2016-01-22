#ifndef SERVERPARSER_H_
#define SERVERPARSER_H_

#include "ServerBoard.h"
#include "ParserHeader.h"

//enum contains options of received move
typedef enum {
  MOVE_OK,
  MOVE_BAD,
  NEW_GAME,
  EXIT_GAME
} MOVE_RESULT;

class ServerParser {
 public:
  /**
   *@brief ctor initialize private object
   */
  ServerParser();

  /**
   *@brief dtor free memory
   */
  virtual ~ServerParser();

  /**
   * @brief function parse received commands and then does them
   * @param [char* receive_buffer] buffer contains command
   * @return true if received command successful
   */
  bool ParseGetBoard(char* receive_buffer);

  /**
   * @brief function parse received move commands and then does them
   * @param [char* receive_buffer] buffer contains command
   * @return done command from MOVE_RESULT
   */
  int ParseReceivedMove(char* receive_buffer);

  /**
   *@brief function call print board
   */
  void ServerParserPrint();

 private:
  ServerBoard* server_board_;
};

#endif
