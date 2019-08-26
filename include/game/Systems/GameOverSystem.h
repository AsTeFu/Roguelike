//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_GAMEOVERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_GAMEOVERSYSTEM_H_

#include "ecs/ISystem.h"

class GameOverSystem : public ISystem {
 private:
  RoomManager* _roomManager;
 protected:
  void postUpdate(Entity *entity) override;

 public:
  GameOverSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                SceneManager *const sceneManager, RoomManager*const roomManager)
      : ISystem(entityManager, systemManager, sceneManager), _roomManager(roomManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_GAMEOVERSYSTEM_H_
