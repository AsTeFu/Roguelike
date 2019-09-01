//
// Created by AsTeFu on 02.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_INPUTSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_INPUTSYSTEM_H_

#include <utilities/KeyCode.h>
#include <map>
#include <vector>
#include "ecs/ISystem.h"

class InputSystem : public ISystem {
 private:
  static std::map<std::vector<KeyCode>, Vector2> buttons;

 protected:
  void preUpdate(Entity *entity) override;

 public:
  InputSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_INPUTSYSTEM_H_
