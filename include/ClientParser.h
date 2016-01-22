#ifndef CLIENTPARSER_H_
#define CLIENTPARSER_H_

#include "ClientBoard.h"
#include "ParserHeader.h"

class ClientParser {
 public:
  /**
   *@brief ctor initialize private object
   */
  ClientParser();

  /**
   *@brief dtor free memory
   */
  virtual ~ClientParser();

  /**
   *@brief function parse received get board response into tokens and does them
   *@param [char* receive_buffer] - received response
   *@return true if get board response is ok, false if fail
   */
  bool ParseGetBoard(char* receive_buffer);

  /**
   *@brief function parse received make move response into tokens and does them
   *@param [char* receive_buffer] - received response
   *@return true if move response is ok, false if move is bad
   */
  bool ParseReceivedMove(char* receive_buffer);

  /**
   *brief function parse received boards data response into tokens and does them
   *@param [char* receive_buffer] - received response
   *@return true if get board response is ok, false if fail
   */
  bool ParseReceivedBoard(char* receive_buffer);

  /**
   *@brief function call print board
   */
  void ClientParserPrint();

 private:
  ClientBoard *client_board_;
};

#endif
