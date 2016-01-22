#ifndef BOARDHEADER_H_
#define BOARDHEADER_H_

#include <cstdlib>

typedef unsigned int uint;
typedef unsigned short ushort;

//enum contains variable move commands
typedef enum  { UP, DOWN, LEFT, RIGHT, BAD } DIRECTION;

const ushort BOARD_SIZE = 4;
const ushort MAX_COORD = 3;
const ushort MIN_COORD = 0;
const ushort MULTI = 2;
const ushort CELL = 1;
const ushort TWO_VAL = 2;
const ushort FOUR_VAL = 4;

#endif
