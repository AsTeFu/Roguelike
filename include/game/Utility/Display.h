//
// Created by AsTeFu on 13.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DISPLAY_H_
#define INCLUDE_GAME_UTILITY_DISPLAY_H_

#include <BearLibTerminal.h>

struct Display {
  char graphic;
  color_t color;

  Display(char graphic, color_t color) : graphic(graphic), color(color) {}
};

#endif  // INCLUDE_GAME_UTILITY_DISPLAY_H_
