//
// Created by AsTeFu on 24.07.2019.
//

#include "game/RoomManager/Builders/RoomReader.h"
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "game/Utility/Vector2.h"

RoomDTO RoomReader::readerRoom(const std::string& path) {
  std::map<char, std::vector<Vector2>> positions;
  std::string buffer;
  std::ifstream file(path);

  int width = 0;
  int height = 0;
  if (file.is_open()) {
    file >> width >> height;
    getline(file, buffer);
    std::cout << "File open: " << path << "; Size: " << width << "x" << height << std::endl;

    int x = 0;
    int y = 0;
    while (getline(file, buffer)) {
      for (const auto& symbol : buffer) {
        positions[symbol].emplace_back(x++, y);
      }
      x = 0;
      y++;
    }
  } else {
    std::cout << "File doesn't exist! " << path << std::endl;
  }

  file.close();

  return RoomDTO(positions, width, height);
}
