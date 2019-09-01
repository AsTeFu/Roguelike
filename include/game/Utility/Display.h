//
// Created by AsTeFu on 13.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DISPLAY_H_
#define INCLUDE_GAME_UTILITY_DISPLAY_H_

#include <utilities/Color.h>

struct Display {
  char graphic;
  Color color;

  Display(char graphic, const Color& color) : graphic(graphic), color(color) {}
};

#endif  // INCLUDE_GAME_UTILITY_DISPLAY_H_
