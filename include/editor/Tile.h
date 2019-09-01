//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_TILE_H_
#define INCLUDE_EDITOR_TILE_H_

#include <game/Utility/Config.h>

class Tile {
 public:
  char graphic;
  Color color;
  Tile(char graphic, const Color& color) : graphic(graphic), color(color) {}
  explicit Tile(char graphic) : graphic(graphic), color(Color::Gray) {}
  Tile() : graphic('.'), color(Config::getInstance().disableColor) {}

  bool operator==(const Tile& rhs) const {
    return graphic == rhs.graphic && color == rhs.color;
  }
  bool operator!=(const Tile& rhs) const {
    return !(rhs == *this);
  }
};

#endif  // INCLUDE_EDITOR_TILE_H_
