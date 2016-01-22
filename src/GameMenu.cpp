#include "GameMenu.h"

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

GameMenu::GameMenu() {
  server_ = new GameServer();
  client_ = new GameClient();
}

void GameMenu::MainMenu() {
  char input;
  short pause = 1;

#ifdef WIN32
  system("cls");
#else
  system("clear");
#endif

  printf("\n                     WELCOME IN 2048 GAME\n\n\n");
  printf("                     [1]Start Game Server\n");
  printf("                     [2]Join Game \n");
  printf("                     [3]Show Rules\n");
  printf("                     [4]Exit\n");

  while (true) {
    printf("                        ");
    scanf(" %c", &input);
    switch (input) {
      //Create server
      case '1':
        if(!server_->StartServer()){
        	sleep(pause);
        	MainMenu();
        }
        break;
        //Connect to the server
      case '2':
        if(!client_->StartConnection()){
        	sleep(pause);
        	MainMenu();
        }
        break;
        //Show game rules
      case '3':
        ShowRules();
        break;
        //Exit application
      case '4':
        printf("                    Good bye!\n");
        sleep(pause);
        exit(pause);
        //wrong option, try again
      default:
        printf("                      Wrong key!\n");
        continue;
    }
  }
}

void GameMenu::ShowRules()
{
#ifdef WIN32
  system("cls");
#else
  system("clear");
#endif

  printf("Rules:\n");
  printf("The rules are that each turn the player must perform a valid move\n");
  printf("shifting all tiles in one direction (up, down, left or right.)\n");
  printf("A move is valid when at least one tile can be moved in that direction.\n");
  printf("When moved against each other tiles with the same number \n");
  printf("on them combine into one.\n");
  printf("A new tile with the value of 2 is spawned at the end of each turn \n");
  printf("if there is an empty spot for it.\n");
  printf("To win the player must create a tile with the number 2048.\n");
  printf("The player loses if no valid moves are possible.\n");

  char input;
  printf("\n\nPress any key to return in main menu\n");
  scanf(" %c", &input);
  MainMenu();
}
GameMenu::~GameMenu() {
  delete server_;
  delete client_;
}

