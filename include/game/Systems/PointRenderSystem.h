//
// Created by  on 06.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_POINTRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_POINTRENDERSYSTEM_H_

#include "ecs/ISystem.h"
#include "game/Components/Graphic.h"
#include "game/Components/PointComponent.h"
#include "game/Components/Transform.h"
#include "game/Utility/Vector2.h"

class PointRenderSystem : public ISystem {
 private:
  bool brezenham(const Vector2 &start, const Vector2 &end) const;

 protected:
  void postUpdate(Entity *entity) override;

 public:
  PointRenderSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                    SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_POINTRENDERSYSTEM_H_
