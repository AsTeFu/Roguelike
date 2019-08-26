//
// Created by  on 09.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_DEALDAMAGESYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_DEALDAMAGESYSTEM_H_

#include <game/Components/DamageEvent.h>
#include "ecs/ISystem.h"

class DealDamageSystem : public ISystem {
 protected:
  void update(Entity *entity) override;
  void postUpdate(Entity *entity) override;

 public:
  DealDamageSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                   SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_DEALDAMAGESYSTEM_H_
