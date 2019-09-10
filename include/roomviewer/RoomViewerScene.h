//
// Created by AsTeFu on 04.09.2019.
//

#ifndef INCLUDE_ROOMVIEWER_ROOMVIEWERSCENE_H_
#define INCLUDE_ROOMVIEWER_ROOMVIEWERSCENE_H_

#include <editor/Components/StructureComponent.h>
#include <game/Scenes/SceneManager.h>
#include <string>
#include <vector>

class RoomViewerScene : public Scene {
 private:
  std::vector<StructureComponent*> _structures;
  std::vector<std::string> _names;
  int currentRoom{0};

  Vector2 _position;
  Vector2 _size;
  Vector2 _offsetPosition;

  int _margin{6};
  int _topMargin{4};

 public:
  RoomViewerScene(Context* const context, SceneManager* sceneManager);
  void start(SceneManager* sceneManager) override;
  void update(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;
  void leftward();
  void rightward();
  void renderStructure(const StructureComponent* structure, const Vector2& position) const;
  void renderSecondaryStructure(const StructureComponent* structure, const Vector2& position, int roomIndex) const;
  void renderName(const Vector2& position, int roomIndex) const;
};

#endif  // INCLUDE_ROOMVIEWER_ROOMVIEWERSCENE_H_
