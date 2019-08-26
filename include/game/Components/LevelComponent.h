//
// Created by  on 20.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_LEVELCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_LEVELCOMPONENT_H_

#include <game/Logs/GameLogger.h>
#include "ecs/IComponent.h"

class LevelComponent : public IComponent {
 public:
  int currentLevel;
  int currentExperience;
  int maxExperience;
  double upgrade;
  double bonus{};
  explicit LevelComponent(int startMaxExperience)
      : currentLevel(1), currentExperience(0), maxExperience(startMaxExperience), upgrade(1.2) {}

  bool addExperience(int experience) {
    currentExperience += static_cast<int>(experience * (bonus + 100) / 100);
    // TODO(ATF): вынести отсюда
    GameLogger::getInstance().add("You killed the enemy and got [color=Sublime]" +
                                  std::to_string(static_cast<int>(experience * (bonus + 100) / 100)) +
                                  "[/color] experience!");

    if (currentExperience >= maxExperience) {
      currentExperience %= maxExperience;
      currentLevel++;
      maxExperience = static_cast<int>(maxExperience * upgrade);
      return true;
    }

    return false;
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_LEVELCOMPONENT_H_
