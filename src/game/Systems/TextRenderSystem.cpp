//
// Created by AsTeFu on 16.09.2019.
//

#include <ecs/EntityManager.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/Lighting.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Systems/RenderSystems/TextRenderSystem.h>
#include <utilities/Terminal.h>

void TextRenderSystem::render(Entity* entity) {
  auto light = entity->getComponent<Lighting>();
  auto graphic = entity->getComponent<Graphic>();

  if (!light->visible) return;

  Terminal::setColor(Config::getInstance().disableColor);
  if (light->isLit) Terminal::setColor(graphic->display.color);
  Terminal::setLayer(graphic->layer);
  Terminal::put(light->renderPos + graphic->offset, graphic->display.graphic);
}
