//
// Created by AsTeFu on 17.09.2019.
//

#include <BearLibTerminal.h>
#include <ecs/EntityManager.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/Lighting.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Systems/RenderSystems/GraphicRenderSystem.h>
#include <utilities/StringUtility.h>
#include <utilities/Terminal.h>
#include <fstream>
#include <string>

GraphicRenderSystem::GraphicRenderSystem(EntityManager* entityManager) : entityManager(entityManager) {
  readSprites();
  for (const auto& symbol : symbols) translateSymbols.emplace(symbol.first, symbol.first + offset);
}
void GraphicRenderSystem::readSprites() {
  std::string buffer;
  std::ifstream file(path);

  if (file.is_open()) {
    std::cout << "File sprites open: " << path << std::endl;

    while (getline(file, buffer)) {
      auto params = StringUtility::split(buffer, ':');
      if (params.size() <= 1 || StringUtility::trimCopy(params[1]).empty()) continue;
      symbols.emplace(params[0][0], params[1]);
    }
  } else {
    std::cout << "File sprites doesn't exist! " << path << std::endl;
  }
  file.close();
}
void GraphicRenderSystem::render(Entity* entity) {
  auto graphic = entity->getComponent<Graphic>();
  auto light = entity->getComponent<Lighting>();

  if (!light->visible) return;

  Terminal::setColor(Config::getInstance().disableColor);
  if (light->isLit) Terminal::setColor(Color::White);
  Terminal::setLayer(graphic->layer);
  Terminal::put(light->renderPos + graphic->offset, translateSymbols[graphic->display.graphic]);
}

void GraphicRenderSystem::start() {
  for (const auto& symbol : translateSymbols)
    terminal_set(((std::to_string(symbol.second)) + ": Resource\\Sprites\\" + symbols[symbol.first]).c_str());
}
void GraphicRenderSystem::end() {
  for (const auto& symbol : translateSymbols) terminal_set((std::to_string(symbol.first) + ": none").c_str());
}
