//
// Created by  on 03.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_CASHTRIGGERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_CASHTRIGGERSYSTEM_H_

#include <game/Components/ItemComponents/CoinItemComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include <game/Logs/GameLogger.h>
#include <algorithm>
#include "ecs/EntityManager.h"
#include "ecs/ISystem.h"
#include "ecs/SystemManager.h"
#include "game/Components/BaseComponent/Transform.h"
#include "game/Components/BaseComponent/Trigger.h"
#include "game/Components/PlayerComponents/PlayerComponent.h"

class CashTriggerSystem : public ISystem {
 protected:
  void update(Entity *entity) override {
    auto coin = entity->getComponent<CoinItemComponent>();
    auto transform = entity->getComponent<Transform>();

    auto player = getEntityManager()->getByTag("player")[0];

    if (transform->position == player->getComponent<Transform>()->position) {
      int addCoins = coin->cost + player->getComponent<SpecialComponent>()->getValue(LUCK) * 2;
      if (player->hasComponent<WalletComponent>())
        player->getComponent<WalletComponent>()->cash += addCoins;


      GameLogger::getInstance().add("[color=yellow]Cash[/color] was picked up [color=yellow](" +
                                    std::to_string(addCoins) + ")");
      getEntityManager()->deleteEntity(entity->getID());
      getSystemManager()->deleteEntity(entity->getID());
    }
  }

 public:
  CashTriggerSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                    SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override {
    return entity->hasComponent<Trigger>() && entity->hasComponent<CoinItemComponent>();
  }
};

#endif  // INCLUDE_GAME_SYSTEMS_CASHTRIGGERSYSTEM_H_
