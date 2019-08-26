//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_COMPONENTS_DIRECTORYCOMPONENT_H_
#define INCLUDE_ROOMCREATOR_COMPONENTS_DIRECTORYCOMPONENT_H_

#include <vector>
#include <string>
#include "ecs/IComponent.h"
#include "roomcreator/Components/FileNameComponent.h"

class DirectoryComponent : public IComponent {
 public:
  // std::vector<FileNameComponent*> directory;
  std::vector<std::string> directory;
};

#endif  // INCLUDE_ROOMCREATOR_COMPONENTS_DIRECTORYCOMPONENT_H_
