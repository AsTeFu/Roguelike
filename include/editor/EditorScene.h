//
// Created by AsTeFu on 21.08.2019.
//

#ifndef INCLUDE_EDITOR_EDITORSCENE_H_
#define INCLUDE_EDITOR_EDITORSCENE_H_

#include <ecs/Engine.h>
#include <game/Scenes/SceneManager.h>
#include <string>
#include <vector>
#include "editor/Tile.h"

class EditorScene : public Scene {
 private:
  Engine _engine;
  const std::string roomsPath{"Resource\\Rooms\\"};
  const std::string brushesPath{"Resource\\Brushes.txt"};
  const std::string colorsPath{"Resource\\ColorsBrushes.txt"};

  const Vector2 filePositions{10, 2};
  const Vector2 colorPositions{10, 33};
  const Vector2 brushPositions{Config::getInstance().sizeTerminal.getX() - 40, 2};
  const Vector2 structurePositions{50, 2};

 public:
  EditorScene(Context* const context, SceneManager* sceneManager);
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void render() override;

  void setBrushes();
  void setColors();
  Entity* readDirectory(const string& path);
  void activateSystem();
  void setCurrentBrush() const;
  void setCurrentBrush(Engine* engine) const;
};

#endif  // INCLUDE_EDITOR_EDITORSCENE_H_
