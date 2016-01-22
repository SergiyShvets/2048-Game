#ifndef SOCKET_H_
#define SOCKET_H_

#include "SocketHeader.h"

class Socket {
 public:
  /**
   *@brief ctor initialize private variables
   */
  Socket();
  virtual ~Socket();
#ifdef WIN32
  /**
   *@brief function initialize Windows socket
   *@return true - successful, false - error
   */
  bool WsaInitialize();
#endif

  /**
   *@brief function creates a socket that is bound to a specific transport service provider
   *@return created socket
   */
  int CreateSocket();

  /**
   *@brief Server function associates a local address with a socket
   *@return true - successful, false - error
   */
  bool BindSocket();

  /**
   *@brief Server function places a socket in a state in which it is listening for an incoming connection
   *@ return true - successful, false - error
   */
  bool ListenSocket();

  /**
   *@brief Server function permits  connection  on a socket
   *@return listen socket
   */
  int AcceptSocket();

  /**
   *@brief Client function establishes a connection to a specified socket
   *@return true - successful, false - error
   */
  bool ConnectSocket();

  /**
   *@brief function sends data on a connected socket
   *@param[const char* sendBuff] pointer to send buffer
   *@return true if send successful
   */
  bool Send(const char* send_buffer);

  /**
   *@brief function receives data from a connected socket.
   *@param[char* recvBuff] pointer to buffer
   *@return true if receive successful
   */
  bool Receive(char* receive_buffer);

  /**
   *@brief function close socket
   */
  void CloseSocket();

 private:
  int client_socket_;
  int listen_socket_;
  struct sockaddr_in address_;
  int address_lenght_;
};

#endif
