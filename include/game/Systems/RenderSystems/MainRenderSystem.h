//
// Created by  on 16.09.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_MAINRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_MAINRENDERSYSTEM_H_

#include <ecs/EntityManager.h>
#include <game/Components/RenderType.h>
#include <game/Systems/RenderSystems/IRenderSystem.h>
#include <vector>
#include "ecs/ISystem.h"

class MainRenderSystem : public ISystem {
 protected:
  void update(Entity *entity) override;
  void postUpdate(Entity *entity) override;

 public:
  MainRenderSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                   SceneManager *const sceneManager, const std::vector<IRenderSystem *> &systems, int start)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
    auto renderType = entityManager->getByTag("renderType")[0]->getComponent<RenderType>();
    for (const auto &system : systems) renderType->renderSystems.push_back(std::unique_ptr<IRenderSystem>(system));
    renderType->currentRenderSystem = renderType->renderSystems[start].get();
    renderType->currentRenderSystem->start();
    renderType->currentIndex = start;
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_MAINRENDERSYSTEM_H_
