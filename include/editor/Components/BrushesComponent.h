//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_COMPONENTS_BRUSHESCOMPONENT_H_
#define INCLUDE_EDITOR_COMPONENTS_BRUSHESCOMPONENT_H_

#include <vector>
#include "editor/Components/BrushComponent.h"
#include "ecs/IComponent.h"

class BrushesComponent : public IComponent {
 public:
  std::vector<BrushComponent*> brushes;
};

#endif  // INCLUDE_EDITOR_COMPONENTS_BRUSHESCOMPONENT_H_
