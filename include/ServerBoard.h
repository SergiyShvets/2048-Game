#ifndef SERVERBOARD_H_
#define SERVERBOARD_H_

#include "BoardHeader.h"
#include "Socket.h"

#include <vector>

// create tile with value
typedef struct Tile {
  Tile()
  : value(0),
    blocked(false) {
  }
  ;
  //placed tile value
  uint value;
  //tile status
  bool blocked;
} Tile;

class ServerBoard {
 public:
  /**
   *@brief ctor initialize board and private variables
   */
  ServerBoard();

  virtual ~ServerBoard();

  /**
   *@brief function print board
   */
  void ServerPrint();

  /**
   *@brief function places tile with value on the board
   *@brief 2 - 90%, value 4 - 10%
   */
  void PlaceTile();

  /**
   *@brief function move values depending on directory (UP,DOWN,RIGHT,LEFT)
   *@param [DIRECTION direction] - move options
   */
  void Move(DIRECTION direction);

  /**
   *@brief function restart the board (clear all values from the board)
   */
  void ClearBoard();

  /**
   * @brief function returns private moved
   */
  bool GetMoved() {
    return moved;
  }

  /**
   * @brief function returns private placed
   */
  bool GetPlaced() {
    return placed;
  }

  bool GameOver();
 private:
  /**
   *@brief function checks if value is in bounds
   *@param [int x] - vertical coordinates
   *@param [int y] - horizontal coordinates
   *@param [uint val] - value
   *@return false if out of bounds
   */
  bool CheckBounds(int x, int y, uint val);

  /**
   *@brief function move values vertically (UP or DOWN)
   *@param [int x] - vertical coordinates
   *@param [int y] - horizontal coordinates
   *@param [int cell] - moved cell
   */
  void MoveVert(int x, int y, int cell);

  /**
   *@brief function move values horizontally (RIGHT or LEFT)
   *@param [int x] - vertical coordinates
   *@param [int y] - horizontal coordinates
   *@param [int cell] - moved cell
   */
  void MoveHor(int x, int y, int cell);

  /**
   *@brief function check if move is possible
   *@return false, if move is possible - true
   */
  bool CheckMove();

  //Game Board matrix 4x4
  std::vector<std::vector<Tile> > board_;
  bool moved;
  bool placed;
  uint score;

};

#endif
