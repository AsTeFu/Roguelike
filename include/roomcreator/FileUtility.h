//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_FILEUTILITY_H_
#define INCLUDE_ROOMCREATOR_FILEUTILITY_H_

#include <roomcreator/Components/StructureComponent.h>
#include <map>
#include <string>
#include "roomcreator/Argb.h"

class FileUtility {
 public:
  static void saveRoom(const std::string& path, StructureComponent* const structure);
  static void readRoom(const std::string& path, StructureComponent* structure);
  static void removeRoom(const std::string& path);
  static StructureComponent* readRoom(const std::string& path);

  static std::map<char, std::string> readBrushes(const std::string& path);
  static std::map<std::string, Argb> readColors(const std::string& path);
};

#endif  // INCLUDE_ROOMCREATOR_FILEUTILITY_H_
