//
// Created by  on 20.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_FINDEVENTSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_FINDEVENTSYSTEM_H_

#include "ecs/ISystem.h"

class FindEventSystem : public ISystem {
 private:
  void spottedEnemy(Entity *enemy);
  void spottedChest(Entity *chest);
  void spottedShop(Entity *shop);

 protected:
  void postUpdate(Entity *entity) override;

 public:
  FindEventSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                  SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_FINDEVENTSYSTEM_H_
