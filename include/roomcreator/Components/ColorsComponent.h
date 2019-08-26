//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_COMPONENTS_COLORSCOMPONENT_H_
#define INCLUDE_ROOMCREATOR_COMPONENTS_COLORSCOMPONENT_H_

#include <roomcreator/Components/ColorComponent.h>
#include <vector>
#include "ecs/IComponent.h"

class ColorsComponent : public IComponent {
 public:
  std::vector<ColorComponent*> colors;
};

#endif  // INCLUDE_ROOMCREATOR_COMPONENTS_COLORSCOMPONENT_H_
