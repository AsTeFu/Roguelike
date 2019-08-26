//
// Created by AsTeFu on 21.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_MENUSCENE_H_
#define INCLUDE_GAME_SCENES_MENUSCENE_H_

#include <algorithm>
#include <string>
#include <vector>

#include "game/Scenes/SceneManager.h"

using std::string;
using std::vector;

enum TypeMenuItem { NewGame = 0, Continue, Setting, Exit };

class MenuScene : public Scene {
  int _menuItem;
  vector<string> _menuItems = {"New game", "Continue", "Setting", "Exit"};

  void inputMenu(SceneManager* context);
  void increase();
  void decrease();
  void enterMenuItem(SceneManager* context);

 public:
  // DECLARE_GET_INSTANCE(MenuScene)

  MenuScene(Context* context, SceneManager* sceneManager) : Scene(context, sceneManager), _menuItem(0) {}
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_MENUSCENE_H_
