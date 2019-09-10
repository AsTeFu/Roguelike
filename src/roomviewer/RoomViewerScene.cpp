//
// Created by AsTeFu on 04.09.2019.
//

#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Input.h>
#include <game/Utility/Utility.h>
#include <roomviewer/RoomViewerScene.h>
#include <utilities/FileUtility.h>
#include <utilities/MathUtility.h>
#include <utilities/Terminal.h>

RoomViewerScene::RoomViewerScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
void RoomViewerScene::start(SceneManager* sceneManager) {
  _structures.clear();
  currentRoom = 0;
  _names = Utility::readDirection("Resource\\Rooms");
  for (const auto& path : _names) _structures.push_back(FileUtility::readRoom("Resource\\Rooms\\" + path));

  _position = {Config::getInstance().sizeTerminal.getX() / 2 - 20, Config::getInstance().sizeTerminal.getY() / 2 - 10};
  _size = Config::getInstance().roomSize;

  _offsetPosition = Vector2(_margin + _size.getX(), 0);
}
void RoomViewerScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::LeftArrow)) leftward();
  if (Input::getKeyDown(KeyCode::RightArrow)) rightward();
  if (Input::getKeyDown(KeyCode::Escape)) sceneManager->switchScene(menuScene);
}
void RoomViewerScene::end(SceneManager* sceneManager) {}
void RoomViewerScene::render() {
  Terminal::clear();

  Terminal::setColor(Color::White);
  SceneRenderUtility::drawHeader({10, 3}, {Config::getInstance().sizeTerminal.getX() - 20, 4}, "Room viewer");

  if (_structures.empty()) return;

  renderStructure(_structures[currentRoom], _position);

  if (currentRoom > 0)
    renderSecondaryStructure(_structures[currentRoom - 1], _position - _offsetPosition, currentRoom - 1);

  if (currentRoom < static_cast<int>(_structures.size()) - 1)
    renderSecondaryStructure(_structures[currentRoom + 1], _position + _offsetPosition, currentRoom + 1);
}
void RoomViewerScene::renderSecondaryStructure(const StructureComponent* structure, const Vector2& position,
                                               int roomIndex) const {
  for (int x = 0; x < structure->size.getX(); ++x)
    for (int y = 0; y < structure->size.getY(); ++y) {
      Color lowAlphaColor = structure->objects[x][y].color;
      lowAlphaColor.a = 120;
      Terminal::setColor(lowAlphaColor);
      Terminal::put(position.getX() + x, _topMargin + position.getY() + y, structure->objects[x][y].graphic);
    }
  renderName(position + Vector2(0, _topMargin), roomIndex);
}
void RoomViewerScene::renderStructure(const StructureComponent* structure, const Vector2& position) const {
  for (int x = 0; x < structure->size.getX(); ++x)
    for (int y = 0; y < structure->size.getY(); ++y)
      Terminal::put(position.getX() + x, position.getY() + y, structure->objects[x][y]);

  renderName(position, currentRoom);
}
void RoomViewerScene::renderName(const Vector2& position, int roomIndex) const {
  Terminal::print(position.getX() + _size.getX() / 2 - _names[roomIndex].size() + 4,
                  position.getY() + _size.getY() + 1, _names[roomIndex]);
}
void RoomViewerScene::leftward() {
  currentRoom = MathUtility::clamp(currentRoom - 1, 0, static_cast<int>(_structures.size()) - 1);
}
void RoomViewerScene::rightward() {
  currentRoom = MathUtility::clamp(currentRoom + 1, 0, static_cast<int>(_structures.size()) - 1);
}
