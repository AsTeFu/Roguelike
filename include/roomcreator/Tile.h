//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_TILE_H_
#define INCLUDE_ROOMCREATOR_TILE_H_

#include <BearLibTerminal.h>
#include <game/Utility/ConfigTerminal.h>

class Tile {
 public:
  char graphic;
  color_t color;
  Tile(char graphic, const color_t& color) : graphic(graphic), color(color) {}
  explicit Tile(char graphic) : graphic(graphic), color(color_from_name("gray")) {}
  Tile() : graphic('.'), color(ConfigTerminal::disableColor) {}
};

#endif  // INCLUDE_ROOMCREATOR_TILE_H_
