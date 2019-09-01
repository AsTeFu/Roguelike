//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_UTILITIES_FILEUTILITY_H_
#define INCLUDE_UTILITIES_FILEUTILITY_H_

#include <editor/Components/StructureComponent.h>
#include <map>
#include <string>
#include <vector>
#include "utilities/Color.h"

class FileUtility {
 public:
  static void saveRoom(const std::string& path, StructureComponent* const structure);
  static void readRoom(const std::string& path, StructureComponent* structure);
  static void removeRoom(const std::string& path);
  static StructureComponent* readRoom(const std::string& path);

  static std::map<char, std::string> readBrushes(const std::string& path);
  static std::map<std::string, Color> readColors(const std::string& path);
  static std::vector<std::string> readDescription(const std::string& path);
};

#endif  // INCLUDE_UTILITIES_FILEUTILITY_H_
