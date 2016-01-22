#include "Socket.h"

#include <stdio.h>

Socket::Socket() {

  listen_socket_ = 0;
  client_socket_ = 0;
  address_lenght_ = sizeof(address_);
  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = inet_addr(IP);
  address_.sin_port = htons(PORT);
}

#ifdef WIN32
bool Socket::WsaInitialize() {

  WSADATA wsaData;

  if ((WSAStartup(MAKEWORD(2, 0), &wsaData)) != SUCCESS_SOCKET) {
    printf("WSAStartup..error\n");
    return false;
  }
  return true;;
}
#endif

int Socket::CreateSocket() {

  client_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (client_socket_ == INVALID_SOCKET) {
    printf("Socket......error\n");
    return false;
  }
  return client_socket_;
}

bool Socket::BindSocket() {

  if ((bind(client_socket_, (struct sockaddr *) &address_, address_lenght_)) != SUCCESS_SOCKET) {
    printf("Bind........error\n");
    return false;
  }
  return true;
}

bool Socket::ListenSocket() {

  if ((listen(client_socket_, SOMAXCONN)) != SUCCESS_SOCKET) {
    printf("Listen......error\n");
    return false;
  }
  return true;
}

int Socket::AcceptSocket() {

  printf("Waiting for client:\n");

  listen_socket_ = accept(client_socket_, (struct sockaddr *) &address_,(socklen_t*)&address_lenght_);

  if (listen_socket_ != SOCKET_ERROR) {

    printf("IP: ");
    printf("%s", inet_ntoa(address_.sin_addr));
    printf("\nPort: ");
    printf("%d\n", ntohs(address_.sin_port));
  } else {
    printf("Accept......error\n");
    return false;
  }

  return listen_socket_;
}

bool Socket::ConnectSocket() {
  if ((connect(client_socket_, (struct sockaddr *) &address_, address_lenght_)) != SUCCESS_SOCKET){
    printf("Connect....error\n");
    return false;
  }
  return true;
}

bool Socket::Receive(char* receive_buffer) {
  //If we want to receive from server we need to use listen socket
  if ((recv(listen_socket_, receive_buffer, BUFF_SIZE, 0)) == SOCKET_ERROR){
    //If we want to receive from client we need to use client socket
    recv(client_socket_, receive_buffer, BUFF_SIZE, 0);
  }
  else
  {
  printf("Received:\n");
  printf("%s\n", receive_buffer);
  }
  return true;
}

bool Socket::Send(const char* send_buffer) {
  //If we want to send from server we need to use listen socket
  if ((send(listen_socket_, send_buffer, strlen(send_buffer), 0)) == SOCKET_ERROR){
    //If we want to send from client we need to use client socket
    send(client_socket_, send_buffer, strlen(send_buffer), 0);
  }
  else
  {
  printf("Send:\n");
  printf("%s\n", send_buffer);
  }
  return true;
}

void Socket::CloseSocket() {
#ifdef WIN32
  WSACleanup();
  closesocket(listen_socket_);
  closesocket(client_socket_);
#else
  close(listen_socket_);
  close(client_socket_);
#endif
}

Socket::~Socket() {

}
