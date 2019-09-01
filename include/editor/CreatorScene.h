//
// Created by AsTeFu on 21.08.2019.
//

#ifndef INCLUDE_EDITOR_CREATORSCENE_H_
#define INCLUDE_EDITOR_CREATORSCENE_H_

#include <ecs/Engine.h>
#include <game/Scenes/SceneManager.h>
#include <string>
#include <vector>
#include "editor/Tile.h"

class CreatorScene : public Scene {
 private:
  Engine _engine;
  const std::string roomsPath{"Resource/Rooms/"};
  const std::string brushesPath{"Resource/Brushes.txt"};
  const std::string colorsPath{"Resource/ColorsBrushes.txt"};

  const Vector2 filePositions{5, 2};
  const Vector2 colorPositions{5, 35};
  const Vector2 brushPositions{Config::getInstance().sizeTerminal.getX() - 50, 2};
  const Vector2 structurePositions{40, 2};

 public:
  CreatorScene(Context* const context, SceneManager* sceneManager);
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void render() override;

  void setBrushes();
  void setColors();
  Entity* readDirectory(const string& path);
  void activateSystem();
};

#endif  // INCLUDE_EDITOR_CREATORSCENE_H_
