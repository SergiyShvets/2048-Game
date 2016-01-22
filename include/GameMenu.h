#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "GameClient.h"
#include "GameServer.h"

class GameMenu
{
 public:
  /**
   *@brief ctor initialize private object
   */
  GameMenu();

  /**
   *@brief dtor free memory
   */
  virtual ~GameMenu();

  /**
   *@brief function start game menu
   */
  void MainMenu();

  /**
   *@brief function show game rules
   */
  void ShowRules();

 private:
  GameServer *server_;
  GameClient *client_;
};

#endif
