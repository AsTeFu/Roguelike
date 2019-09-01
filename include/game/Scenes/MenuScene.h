//
// Created by AsTeFu on 21.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_MENUSCENE_H_
#define INCLUDE_GAME_SCENES_MENUSCENE_H_

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "game/Scenes/SceneManager.h"

enum TypeMenuItem { NewGame = 0, Continue, Setting, Exit };

using std::bind;
using std::function;
using std::make_pair;
using std::map;
using std::string;
using std::vector;
using std::placeholders::_1;

class MenuScene : public Scene {
  int _layer{47};
  Vector2 position;
  Vector2 positionPica{5, 2};
  string cursor{"=>"};

  int _currentElement;
  vector<string> _namesMenuElements;
  map<string, function<void(SceneManager*)> > _menuElements;

  void upward();
  void downward();
  void enterMenuItem(SceneManager* sceneManager);

  void newGame(SceneManager* sceneManager);
  void editor(SceneManager* sceneManager);
  void exit(SceneManager* sceneManager);
  void setting(SceneManager* sceneManager);
  void continueGame(SceneManager* sceneManager);
  void drawPica() const;
  void drawCursor() const;

 public:
  MenuScene(Context* context, SceneManager* sceneManager);
  void start(SceneManager* sceneManager) override;
  void render() override;
  void update(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
};

#endif  // INCLUDE_GAME_SCENES_MENUSCENE_H_
