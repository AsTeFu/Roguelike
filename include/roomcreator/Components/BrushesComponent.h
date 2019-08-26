//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_COMPONENTS_BRUSHESCOMPONENT_H_
#define INCLUDE_ROOMCREATOR_COMPONENTS_BRUSHESCOMPONENT_H_

#include <vector>
#include "roomcreator/Components/BrushComponent.h"
#include "ecs/IComponent.h"

class BrushesComponent : public IComponent {
 public:
  std::vector<BrushComponent*> brushes;
};

#endif  // INCLUDE_ROOMCREATOR_COMPONENTS_BRUSHESCOMPONENT_H_
