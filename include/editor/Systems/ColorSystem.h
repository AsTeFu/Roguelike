//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_SYSTEMS_COLORSYSTEM_H_
#define INCLUDE_EDITOR_SYSTEMS_COLORSYSTEM_H_

#include "ecs/ISystem.h"

class ColorSystem : public ISystem {
 private:
  Vector2 _position;
  int _currentColor{};

 protected:
  void update(Entity* entity) override;
  void postUpdate(Entity* entity) override;

 public:
  ColorSystem(EntityManager* const entityManager, SystemManager* const systemManager,
                   SceneManager* const sceneManager, const Vector2& position)
      : ISystem(entityManager, systemManager, sceneManager), _position(position) {
    updateComponents();
  }
  bool filter(Entity* entity) const override;
};

#endif  // INCLUDE_EDITOR_SYSTEMS_COLORSYSTEM_H_
