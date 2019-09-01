//
// Created by AsTeFu on 22.08.2019.
//

#include "utilities/FileUtility.h"
#include <editor/Components/ColorComponent.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void FileUtility::saveRoom(const std::string& path, StructureComponent* const structure) {
  std::ofstream file(path);

  if (file.is_open()) {
    file << "Width: " << structure->size.getX() << std::endl;
    file << "Height: " << structure->size.getY() << std::endl;

    for (int i = 0; i < structure->size.getX(); ++i) {
      for (int j = 0; j < structure->size.getY(); ++j) {
        if (structure->objects[i][j].graphic != '.') {
          Color color = structure->objects[i][j].color;
          file << i << " " << j << " { color: " << color.a << " " << color.r << " " << color.g << " " << color.b
               << " } graphic: " << structure->objects[i][j].graphic << " }" << std::endl;
        }
      }
    }

    std::cout << "File room save " << path << std::endl;
  } else {
    std::cout << "File room doesn't exist! " << path << std::endl;
  }

  file.close();
}
void FileUtility::readRoom(const std::string& path, StructureComponent* structure) {
  std::ifstream file(path);

  int width = 0;
  int height = 0;

  if (file.is_open()) {
    file.ignore(7);
    file >> width;
    file.ignore(9);
    file >> height;
    file.ignore();

    structure->size = Vector2(width, height);

    for (int i = 0; i < width; ++i) {
      for (int j = 0; j < height; ++j) {
        structure->objects[i][j] = Tile();
      }
    }

    while (!file.eof()) {
      int x, y;
      file >> x >> y;
      file.ignore(10);
      int a, r, g, b;
      file >> a >> r >> g >> b;
      structure->objects[x][y].color = Color(a, r, g, b);
      file.ignore(11);
      file >> structure->objects[x][y].graphic;
      file.ignore(3);
    }

    std::cout << "File room read " << path << std::endl;
  } else {
    std::cout << "File room doesn't exist! " << path << std::endl;
  }

  file.close();
}
std::map<char, std::string> FileUtility::readBrushes(const std::string& path) {
  std::ifstream file(path);
  std::string buffer;
  char symbol;
  std::map<char, std::string> brushes;

  if (file.is_open()) {
    while (!file.eof()) {
      file >> symbol >> buffer;

      brushes[symbol] = buffer;
      file.ignore();
    }

    std::cout << "File brushes read " << path << std::endl;
  } else {
    std::cout << "File brushes doesn't exist! " << path << std::endl;
  }

  file.close();

  return brushes;
}
std::map<std::string, Color> FileUtility::readColors(const std::string& path) {
  std::ifstream file(path);
  std::string name;
  std::map<std::string, Color> colors;
  Color argb(0, 0, 0, 0);

  if (file.is_open()) {
    while (!file.eof()) {
      file >> argb.a >> argb.r >> argb.g >> argb.b >> name;

      colors.emplace(name, argb);
      file.ignore();
    }

    std::cout << "File colors read " << path << std::endl;
  } else {
    std::cout << "File colors doesn't exist! " << path << std::endl;
  }

  file.close();

  return colors;
}
StructureComponent* FileUtility::readRoom(const std::string& path) {
  std::ifstream file(path);
  StructureComponent* structure;
  int width = 0;
  int height = 0;

  if (file.is_open()) {
    file.ignore(7);
    file >> width;
    file.ignore(9);
    file >> height;
    file.ignore();

    structure = new StructureComponent(width, height);
    structure->size = Vector2(width, height);
    while (!file.eof()) {
      int x, y;
      file >> x >> y;
      file.ignore(10);
      int a, r, g, b;
      file >> a >> r >> g >> b;
      structure->objects[x][y].color = Color(a, r, g, b);
      file.ignore(11);
      file >> structure->objects[x][y].graphic;
      file.ignore(3);
    }

    std::cout << "File room read " << path << std::endl;
    file.close();
    return structure;
  } else {
    std::cout << "File room doesn't exist! " << path << std::endl;
    return nullptr;
  }
}
void FileUtility::removeRoom(const std::string& path) {
  remove(path.c_str());
}
std::vector<std::string> FileUtility::readDescription(const std::string& path) {
  std::string buffer;
  std::vector<std::string> description;
  std::ifstream file(path);

  if (file.is_open()) {
    while (getline(file, buffer)) {
      if (buffer.at(0) == '#') {
        continue;
      }
      description.push_back(buffer);
    }

    file.close();
  } else {
    std::cout << "File description doesn't exits!" << std::endl;
  }
  return description;
}
