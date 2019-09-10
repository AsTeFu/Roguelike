//
// Created by  on 20.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_LEVELCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_LEVELCOMPONENT_H_

#include <utilities/Random.h>
#include <game/Logs/GameLogger.h>
#include <game/Utility/Config.h>
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
  LevelComponent() : LevelComponent(100) {}
  LevelComponent(const LevelComponent& levelComponent)
      : currentLevel(levelComponent.currentLevel),
        currentExperience(levelComponent.currentExperience),
        maxExperience(levelComponent.maxExperience),
        upgrade(levelComponent.upgrade),
        bonus(levelComponent.bonus) {}

  int addExperience() {
    int experience = static_cast<int>(Random::random(Config::getInstance().experienceRange) * (bonus + 100) / 100);
    currentExperience += experience;
    return experience;
  }
  bool isLevelUp() {
    return currentExperience >= maxExperience;
  }
  void levelUp() {
    currentExperience %= maxExperience;
    currentLevel++;
    maxExperience = static_cast<int>(maxExperience * upgrade);
  }
  void setExperience(LevelComponent* levelComponent) {
    currentLevel = levelComponent->currentLevel;
    currentExperience = levelComponent->currentExperience;
    maxExperience = levelComponent->maxExperience;
    upgrade = levelComponent->upgrade;
    bonus = levelComponent->bonus;
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_LEVELCOMPONENT_H_
