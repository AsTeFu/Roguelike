//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_SCENES_SCENERENDERUTILITY_H_
#define INCLUDE_GAME_SCENES_SCENERENDERUTILITY_H_

#include <utilities/Vector2.h>
#include <string>

class SceneRenderUtility {
 public:
  static void drawHeader(const Vector2& position, const Vector2& size, const std::string& name);
  static void drawHeader(int x, int y, int w, int h, const std::string& name);
  static void drawBorder(const Vector2& position, const Vector2& size);
  static void drawBorder(int x, int y, int w, int h);
  static void verticalBorder(const Vector2& position, const Vector2& size);
  static void verticalBorder(int x, int y, int w, int h);
  static void horizontalBorder(const Vector2& position, const Vector2& size);
  static void horizontalBorder(int x, int y, int w, int h);
  static void horizontalLine(int x, int y, int len);
  static void horizontalLine(const Vector2& position, int len);
  static void verticalLine(int x, int y, int len);
  static void verticalLine(const Vector2& position, int len);
};

#endif  // INCLUDE_GAME_SCENES_SCENERENDERUTILITY_H_
