//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_COMPONENTS_FILENAMECOMPONENT_H_
#define INCLUDE_ROOMCREATOR_COMPONENTS_FILENAMECOMPONENT_H_

#include <game/Utility/Utility.h>
#include <string>
#include <utility>
#include <vector>
#include "ecs/IComponent.h"

class FileNameComponent : public IComponent {
 public:
  std::string fileName;
  explicit FileNameComponent(std::string fileName) : fileName(std::move(fileName)) {}
};

#endif  // INCLUDE_ROOMCREATOR_COMPONENTS_FILENAMECOMPONENT_H_
