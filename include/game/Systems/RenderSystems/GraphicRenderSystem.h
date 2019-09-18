//
// Created by  on 16.09.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_GRAPHICRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_GRAPHICRENDERSYSTEM_H_

#include <game/Components/BaseComponent/Transform.h>
#include <map>
#include <string>
#include "ecs/ISystem.h"
#include "game/Systems/RenderSystems/IRenderSystem.h"

class GraphicRenderSystem : public IRenderSystem {
 private:
  EntityManager *entityManager;
  std::map<int, int> translateSymbols;
  std::map<int, std::string> symbols;
  std::string path{"Resource\\Sprites.txt"};
  int offset = 100;

  void readSprites();

 public:
  void start() override;
  void end() override;

  void render(Entity *entity) override;
  explicit GraphicRenderSystem(EntityManager *entityManager);
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_GRAPHICRENDERSYSTEM_H_
