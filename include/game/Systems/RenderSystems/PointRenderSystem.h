//
// Created by  on 06.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_POINTRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_POINTRENDERSYSTEM_H_

#include "ecs/ISystem.h"
#include "game/Components/BaseComponent/Graphic.h"
#include "game/Components/BaseComponent/Transform.h"
#include "game/Components/EnvironmentComponents/PointComponent.h"
#include "utilities/Vector2.h"

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

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_POINTRENDERSYSTEM_H_
