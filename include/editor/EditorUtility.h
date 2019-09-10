//
// Created by AsTeFu on 25.08.2019.
//

#ifndef INCLUDE_EDITOR_EDITORUTILITY_H_
#define INCLUDE_EDITOR_EDITORUTILITY_H_

#include <ecs/Engine.h>
#include <editor/Components/DirectoryComponent.h>
#include <string>
#include "utilities/FileUtility.h"

class EditorUtility {
 public:
  static Entity* createEmptyStructure(Entity* structureEntity) {
    auto structure = structureEntity->getComponent<StructureComponent>();

    for (int i = 0; i < structure->size.getX(); ++i) {
      for (int j = 0; j < structure->size.getY(); ++j) {
        structure->objects[i][j] = Tile();
      }
    }
    for (int i = 0; i < structure->size.getX(); i++) {
      structure->objects[i][0] = Tile('#');
      structure->objects[i][structure->size.getY() - 1] = Tile('#');
    }
    for (int j = 0; j < structure->size.getY(); j++) {
      structure->objects[0][j] = Tile('#');
      structure->objects[structure->size.getX() - 1][j] = Tile('#');
    }

    return structureEntity;
  }
  static void addEmptyRoom(const std::string& roomsPath, Entity* structureEntity, DirectoryComponent* directory) {
    auto structure = EditorUtility::createEmptyStructure(structureEntity)->getComponent<StructureComponent>();

    std::string name = "room" + std::to_string(directory->directory.size()) + ".room";
    FileUtility::saveRoom(roomsPath + name, structure);
    directory->directory.emplace_back(name);
  }
  static Entity* createStructure(Engine* engine) {
    auto roomStruct = engine->getEntityManager()->createEntity("struct");
    roomStruct->addComponent<StructureComponent>(41, 21);
    return roomStruct;
  }
};

#endif  // INCLUDE_EDITOR_EDITORUTILITY_H_
