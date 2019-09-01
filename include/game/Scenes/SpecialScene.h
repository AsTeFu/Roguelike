//
// Created by AsTeFu on 26.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_SPECIALSCENE_H_
#define INCLUDE_GAME_SCENES_SPECIALSCENE_H_

#include <map>
#include <string>
#include <vector>
#include "game/Player/Special.h"
#include "game/Scenes/SceneManager.h"

using std::map;
using std::string;
using std::vector;

class SpecialScene : public Scene {
  vector<string> _description;
  int _currentPos;
  Special _special;

  int lineLen{60};
  Vector2 positionStats;
  Vector2 sizeStats;
  Vector2 positionDescription;
  Vector2 sizeDescription;
  Vector2 positionLabel;
  Vector2 sizeLabel;
  int leftMargin{5};
  int topMargin{3};
  std::string _cursor{"=>"};

  void downward();
  void upward();
  void increaseCurrentStat();
  void decreaseCurrentStat();

  void switchColor(const string& stat) const;
  void drawInputButtons(int x, int y, const string& stat) const;

  void drawDescription(int x, int y) const;
  int drawStat(int x, int y, const string& stat) const;
  int renderDescriptions(int x, int y) const;
  int renderStat(int x, int y) const;

 public:
  SpecialScene(Context* context, SceneManager* sceneManager);
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_SPECIALSCENE_H_
