//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_COMPONENTS_DIRECTORYCOMPONENT_H_
#define INCLUDE_EDITOR_COMPONENTS_DIRECTORYCOMPONENT_H_

#include <vector>
#include <string>
#include "ecs/IComponent.h"
#include "editor/Components/FileNameComponent.h"

class DirectoryComponent : public IComponent {
 public:
  // std::vector<FileNameComponent*> directory;
  std::vector<std::string> directory;
};

#endif  // INCLUDE_EDITOR_COMPONENTS_DIRECTORYCOMPONENT_H_
