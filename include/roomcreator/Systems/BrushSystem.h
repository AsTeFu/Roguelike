//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_SYSTEMS_BRUSHSYSTEM_H_
#define INCLUDE_ROOMCREATOR_SYSTEMS_BRUSHSYSTEM_H_

#include "ecs/ISystem.h"

class BrushSystem : public ISystem {
 private:
  Vector2 _position;
  int _currentBrush{};

 protected:
  void update(Entity* entity) override;
  void postUpdate(Entity* entity) override;

 public:
  BrushSystem(EntityManager* const entityManager, SystemManager* const systemManager, SceneManager* const sceneManager,
              const Vector2& position)
      : ISystem(entityManager, systemManager, sceneManager), _position(position) {
    updateComponents();
  }
  bool filter(Entity* entity) const override;
};

#endif  // INCLUDE_ROOMCREATOR_SYSTEMS_BRUSHSYSTEM_H_
