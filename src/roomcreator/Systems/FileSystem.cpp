//
// Created by AsTeFu on 22.08.2019.
//

#include <BearLibTerminal.h>
#include <ecs/EntityManager.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/Input.h>
#include <roomcreator/Components/DirectoryComponent.h>
#include <roomcreator/Components/StructureComponent.h>
#include <roomcreator/CreatorUtility.h>
#include <roomcreator/FileUtility.h>
#include <roomcreator/Systems/FileSystem.h>
#include <algorithm>
#include <string>

bool FileSystem::filter(Entity* entity) const {
  return entity->hasComponent<DirectoryComponent>();
}

void FileSystem::update(Entity* entity) {
  if (Input::isPressed(TK_DOWN) || Input::isPressed(TK_S)) {
    if (_currentPos < static_cast<int>(entity->getComponent<DirectoryComponent>()->directory.size()) - 1) {
      saveFile(entity);
      _currentFile++;
      _currentPos++;
      selectFile(entity);
    }
  }
  if (Input::isPressed(TK_UP) || Input::isPressed(TK_W)) {
    if (_currentPos > 0) {
      saveFile(entity);
      _currentFile--;
      _currentPos--;
      selectFile(entity);
    }
  }

  if (Input::isPressed(TK_S) && terminal_check(TK_CONTROL)) {
    saveFile(entity);
  }

  if (Input::isPressed(TK_N) && terminal_check(TK_CONTROL)) {
    saveFile(entity);
    newFile(entity);
  }

  if (Input::isPressed(TK_R) && terminal_check(TK_CONTROL)) {
    deleteFile(entity);
    selectFile(entity);
  }
}
void FileSystem::deleteFile(const Entity* entity) {
  auto directory = entity->getComponent<DirectoryComponent>();
  FileUtility::removeRoom(_roomsPath + directory->directory[_currentFile]);

  directory->directory.erase(directory->directory.begin() + _currentFile);

  if (_currentPos == static_cast<int>(directory->directory.size()) && _currentPos > 0) {
    _currentPos--;
    _currentFile--;
  }
}
void FileSystem::newFile(const Entity* entity) {
  auto roomStruct = getEntityManager()->getByTag("struct")[0];
  auto structure = CreatorUtility::createEmptyStructure(roomStruct)->getComponent<StructureComponent>();

  auto directory = entity->getComponent<DirectoryComponent>();
  std::string name = "room" + std::to_string(directory->directory.size());
  FileUtility::saveRoom(_roomsPath + name, structure);
  directory->directory.emplace_back(name);

  _currentFile = _currentPos = static_cast<int>(directory->directory.size()) - 1;
}
void FileSystem::saveFile(const Entity* entity) const {
  auto structure = getEntityManager()->getByTag("struct")[0]->getComponent<StructureComponent>();
  FileUtility::saveRoom(_roomsPath + entity->getComponent<DirectoryComponent>()->directory[_currentFile], structure);
}
void FileSystem::selectFile(const Entity* entity) const {
  auto structure = getEntityManager()->getByTag("struct")[0]->getComponent<StructureComponent>();
  FileUtility::readRoom(_roomsPath + entity->getComponent<DirectoryComponent>()->directory[_currentPos], structure);
}

void FileSystem::postUpdate(Entity* entity) {
  Vector2 size(30, 30);
  terminal_layer(0);
  terminal_crop(_position.getX(), _position.getY(), size.getX(), size.getY());
  terminal_clear_area(_position.getX(), _position.getY(), size.getX(), size.getY());

  terminal_color("white");

  int offsetX = _position.getX();
  int offsetY = _position.getY();

  Utility::drawBorder({offsetX, offsetY}, size);

  offsetX += 2;
  offsetY += 2;

  terminal_printf(offsetX, offsetY, "Saved rooms:");

  offsetX += 4;
  offsetY += 2;

  auto directory = entity->getComponent<DirectoryComponent>();
  int offset = std::max(0, _currentPos + _maxDisplayFile / 2 - static_cast<int>(directory->directory.size()));
  int start = std::max(0, _currentPos - _maxDisplayFile / 2 - offset);
  int end = std::min(start + _maxDisplayFile, static_cast<int>(directory->directory.size()));

  for (int i = start; i < end; ++i) {
    if (_currentPos == i) {
      terminal_print(offsetX - 3, offsetY, "=>");
      terminal_color("white");
    } else {
      terminal_color("gray");
    }

    terminal_print(offsetX, offsetY++, directory->directory[i].c_str());
  }

  offsetY += 2;

  terminal_color("white");
  terminal_printf(offsetX, offsetY++, "New file - CTRL+N");
  terminal_printf(offsetX, offsetY++, "Save file - CTRL+S");
  terminal_printf(offsetX, offsetY++, "Remove file - CTRL+R");
  terminal_printf(offsetX, offsetY++, "Clear file - CTRL+C");
}
