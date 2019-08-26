//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_MEDKITTRIGGERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_MEDKITTRIGGERSYSTEM_H_

#include "ecs/ISystem.h"

class MedkitTriggerSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  MedkitTriggerSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                      SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_MEDKITTRIGGERSYSTEM_H_
