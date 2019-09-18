//
// Created by  on 16.09.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_RENDERTYPE_H_
#define INCLUDE_GAME_COMPONENTS_RENDERTYPE_H_

#include <ecs/Entity.h>
#include <game/Systems/RenderSystems/IRenderSystem.h>
#include <vector>
#include "ecs/IComponent.h"

class RenderType : public IComponent {
 public:
  std::vector<std::unique_ptr<IRenderSystem>> renderSystems;
  IRenderSystem *currentRenderSystem;
  size_t currentIndex{0};
};

#endif  // INCLUDE_GAME_COMPONENTS_RENDERTYPE_H_
