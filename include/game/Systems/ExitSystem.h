//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_EXITSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_EXITSYSTEM_H_

#include "ecs/ISystem.h"

class ExitSystem : public ISystem {
 private:
  RoomManager* _roomManager;
  bool isActivate;
 protected:
  void preUpdate(Entity *entity) override;
  void postUpdate(Entity *entity) override;

 public:
  ExitSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager,
             RoomManager *const roomManager)
      : ISystem(entityManager, systemManager, sceneManager), _roomManager(roomManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_EXITSYSTEM_H_
