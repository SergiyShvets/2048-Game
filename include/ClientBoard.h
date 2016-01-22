#ifndef CLIENTBOARD_H_
#define CLIENTBOARD_H_

#include "BoardHeader.h"
#include <vector>
#include <string>

class ClientBoard {
 public:
  /**
   *@brief ctor initialize board
   */
  ClientBoard();
  virtual ~ClientBoard();

  /**
   *@brief function print board
   */
  void Client_Print();

  /**
   *@brief function checks if value is in bounds
   *@param [int x] - vertical coordinates
   *@param [int y] - horizontal coordinates
   *@param [char* tile_value] - value of tile
   *@param [char* score_value] - game score
   */
  void Client_Place(int x0, int y0, char* tile_value, char* score_value);

 private:
  //Client Board matrix 4x4
  std::vector<std::vector<std::string> > board_;
  std::string score_;
};

#endif
