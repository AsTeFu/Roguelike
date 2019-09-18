//
// Created by AsTeFu on 16.09.2019.
//

#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/RenderType.h>
#include <game/Systems/RenderSystems/MainRenderSystem.h>
#include <game/Utility/DTO/RenderModeDTO.h>
#include <game/Utility/Input.h>

bool MainRenderSystem::filter(Entity* entity) const {
  return entity->hasComponent<RenderType>();
}
void MainRenderSystem::update(Entity* entity) {
  auto renderType = entity->getComponent<RenderType>();

  // Тут грязно
  if (Input::getKeyDown(KeyCode::P)) {
    renderType->currentRenderSystem->end();
    renderType->currentRenderSystem =
        renderType->renderSystems[++renderType->currentIndex % renderType->renderSystems.size()].get();
    getSceneManager()->getContext()->getObject<RenderModeDTO>()->mode =
        !getSceneManager()->getContext()->getObject<RenderModeDTO>()->mode;
    renderType->currentRenderSystem->start();
  }
}
void MainRenderSystem::postUpdate(Entity* entity) {
  auto renderType = entity->getComponent<RenderType>();
  for (auto& graphic : *getEntityManager())
    if (graphic.hasComponent<Graphic>()) renderType->currentRenderSystem->render(&graphic);
}
