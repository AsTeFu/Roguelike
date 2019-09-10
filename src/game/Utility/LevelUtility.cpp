//
// Created by AsTeFu on 30.08.2019.
//

#include <utilities/Random.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Utility/Config.h>
#include <game/Utility/LevelUtility.h>

void LevelUtility::addExperience(Entity* player) {
  auto level = player->getComponent<LevelComponent>();
  int experience = level->addExperience();
  GameLogger::getInstance().add("You killed the enemy and got [color=Sublime]" + std::to_string(experience) +
                                "[/color] experience!");
  if (level->isLevelUp()) levelUp(player, level);
}
void LevelUtility::levelUp(const Entity* player, LevelComponent* level) {
  level->levelUp();
  player->getComponent<SpecialComponent>()->special.addAvailablePoint();
  player->getComponent<AbilitiesComponent>()->available++;
  GameLogger::getInstance().add("[color=Sublime]Level Up!");
}
