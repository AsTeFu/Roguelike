//
// Created by AsTeFu on 22.08.2019.
//

#include "roomcreator/FileUtility.h"
#include <roomcreator/Components/ColorComponent.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

void FileUtility::saveRoom(const std::string& path, StructureComponent* const structure) {
  std::ofstream file(path);

  if (file.is_open()) {
    file << "Width: " << structure->size.getX() << std::endl;
    file << "Height: " << structure->size.getY() << std::endl;

    for (int i = 0; i < structure->size.getX(); ++i) {
      for (int j = 0; j < structure->size.getY(); ++j) {
        if (structure->objects[i][j].graphic != '.')
          file << i << " " << j << " { color: " << structure->objects[i][j].color
               << " graphic: " << structure->objects[i][j].graphic << " }" << std::endl;
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
      file >> structure->objects[x][y].color;
      file.ignore(10);
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
std::map<std::string, Argb> FileUtility::readColors(const std::string& path) {
  std::ifstream file(path);
  std::string name;
  std::map<std::string, Argb> colors;
  Argb argb(0, 0, 0, 0);

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
      file >> structure->objects[x][y].color;
      file.ignore(10);
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
