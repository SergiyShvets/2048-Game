#ifndef SOCKETHEADER_H_
#define SOCKETHEADER_H_

//enum of windows and linux platforms
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define SUCCESS_SOCKET  0

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET 0
#endif

typedef unsigned int uint;
typedef unsigned short ushort;

const ushort IP_SIZE = 16;
const char IP[IP_SIZE] = "127.0.0.1";
const ushort PORT = 9999;
const ushort BUFF_SIZE = 256;

// send and receive packet
struct Packet {
  char buffer[BUFF_SIZE];
};

#endif
