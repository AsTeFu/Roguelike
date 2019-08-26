//
// Created by AsTeFu on 26.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_SPECIALSCENE_H_
#define INCLUDE_GAME_SCENES_SPECIALSCENE_H_

#include <BearLibTerminal.h>
#include <map>
#include <string>
#include <vector>
#include "game/Player/Special.h"
#include "game/Scenes/SceneManager.h"

using std::vector;
using std::map;
using std::string;

class SpecialScene : public Scene {
  vector<string> _desription;
  int _currentPos;
  Special _special;
  // int _currentValue;

  void inputMenu(SceneManager* sceneManager);
  void decrease();
  void increase();
  void upStat();
  void downStat();

 public:
  SpecialScene(Context* context, SceneManager* sceneManager);
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;

  static vector<string> split(const string& s, char regex);
};

#endif  // INCLUDE_GAME_SCENES_SPECIALSCENE_H_
