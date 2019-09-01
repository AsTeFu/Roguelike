//
// Created by AsTeFu on 02.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_INPUTKEYBOARD_H_
#define INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_INPUTKEYBOARD_H_

#include <map>
#include "ecs/IComponent.h"
#include "game/Utility/Display.h"

class InputKeyboard : public IComponent {
 public:
  int key;
  std::map<int, bool> downs;
};

#endif  // INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_INPUTKEYBOARD_H_
