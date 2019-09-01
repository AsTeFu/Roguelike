//
// Created by AsTeFu on 30.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_LEVELUTILITY_H_
#define INCLUDE_GAME_UTILITY_LEVELUTILITY_H_

#include <ecs/Entity.h>
#include <game/Components/PlayerComponents/LevelComponent.h>

class LevelUtility {
 private:
  static void levelUp(const Entity* player, LevelComponent* level);

 public:
  static void addExperience(Entity* player);
};

#endif  // INCLUDE_GAME_UTILITY_LEVELUTILITY_H_
