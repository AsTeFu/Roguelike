//
// Created by AsTeFu on 31.08.2019.
//

#include <game/Scenes/SceneRenderUtility.h>
#include <utilities/Terminal.h>
#include <string>

void SceneRenderUtility::drawHeader(const Vector2& position, const Vector2& size, const std::string& name) {
  drawHeader(position.getX(), position.getY(), size.getX(), size.getY(), name);
}
void SceneRenderUtility::drawHeader(int x, int y, int w, int h, const std::string& name) {
  Terminal::print(x + w / 2 - static_cast<int>(name.size()) / 2, y - 1 + h / 2, name);

  horizontalBorder(x, y, w, h);
  verticalBorder(x, y, w, h);
}
void SceneRenderUtility::horizontalBorder(const Vector2& position, const Vector2& size) {
  horizontalBorder(position.getX(), position.getY(), size.getX(), size.getY());
}
void SceneRenderUtility::horizontalBorder(int x, int y, int w, int h) {
  horizontalLine(x, y, w);
  horizontalLine(x, y + h - 1, w);
}
void SceneRenderUtility::verticalBorder(const Vector2& position, const Vector2& size) {
  verticalBorder(position.getX(), position.getY(), size.getX(), size.getY());
}
void SceneRenderUtility::verticalBorder(int x, int y, int w, int h) {
  verticalLine(x, y, h);
  verticalLine(x + w - 1, y, h);
}
void SceneRenderUtility::horizontalLine(int x, int y, int len) {
  for (int i = 0; i < len; i++) Terminal::put(x + i, y, '=');
}
void SceneRenderUtility::verticalLine(int x, int y, int len) {
  for (int i = 1; i < len - 1; i++) Terminal::put(x, y + i, '|');
}
void SceneRenderUtility::horizontalLine(const Vector2& position, int len) {
  horizontalLine(position.getX(), position.getY(), len);
}
void SceneRenderUtility::verticalLine(const Vector2& position, int len) {
  verticalLine(position.getX(), position.getY(), len);
}
void SceneRenderUtility::drawBorder(const Vector2& position, const Vector2& size) {
  drawBorder(position.getX(), position.getY(), size.getX(), size.getY());
}
void SceneRenderUtility::drawBorder(int x, int y, int w, int h) {
  horizontalBorder(x, y, w, h);
  verticalBorder(x, y, w, h);
}
