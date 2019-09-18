//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_UTILITIES_TERMINAL_H_
#define INCLUDE_UTILITIES_TERMINAL_H_

#include <editor/Tile.h>
#include <string>
#include "utilities/Color.h"
#include "utilities/Vector2.h"

class Terminal {
 public:
  static void start();
  static void refresh();
  static void close();

  static void setColor(Color color);
  static void clearArea(int x, int y, int w, int h);
  static void clearArea(const Vector2& position, const Vector2& size);
  static void clear();
  static void crop(int x, int y, int w, int h);
  static void crop(const Vector2& position, const Vector2& size);
  static void setLayer(int layer);
  static void put(int x, int y, int symbol);
  static void put(const Vector2& position, int symbol);
  static void put(const Vector2& position, const Tile& tile);
  static void put(int x, int y, const Tile& tile);
  static void print(int x, int y, const std::string& str);
  static void print(const Vector2& position, const std::string& str);
  static void printf(int x, int y, const char* str, ...);
  static void printf(const Vector2& position, const char* str, ...);
  static Color pickColor(int x, int y, int index);
  static Color pickColor(const Vector2& position, int index);
  static Tile pick(int x, int y, int index);
  static std::string readString(int x, int y, int max);
  static std::string readString(const Vector2& position, int max);
  static void enableMouse();
};

#endif  // INCLUDE_UTILITIES_TERMINAL_H_
