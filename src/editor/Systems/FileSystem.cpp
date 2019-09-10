//
// Created by AsTeFu on 22.08.2019.
//

#include <ecs/EntityManager.h>
#include <editor/Components/DirectoryComponent.h>
#include <editor/Components/StructureComponent.h>
#include <editor/EditorUtility.h>
#include <editor/Systems/FileSystem.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Config.h>
#include <game/Utility/Input.h>
#include <utilities/FileUtility.h>
#include <utilities/StringUtility.h>
#include <utilities/Terminal.h>
#include <algorithm>
#include <string>

FileSystem::FileSystem(EntityManager* const entityManager, SystemManager* const systemManager,
                       SceneManager* const sceneManager, const Vector2& position, std::string path)
    : ISystem(entityManager, systemManager, sceneManager), _position(position), _roomsPath(std::move(path)) {
  updateComponents();
  _size = {30, 30};
}

bool FileSystem::filter(Entity* entity) const {
  return entity->hasComponent<DirectoryComponent>();
}

void FileSystem::update(Entity* entity) {
  if (Input::getKey(KeyCode::S) && Input::check(KeyCode::CTRL)) {
    saveFile(entity);
  } else if (Input::getKey(KeyCode::DownArrow) || Input::getKey(KeyCode::S)) {
    downward(entity);
  } else if (Input::getKey(KeyCode::UpArrow) || Input::getKey(KeyCode::W)) {
    upward(entity);
  } else if (Input::getKey(KeyCode::N) && Input::check(KeyCode::CTRL)) {
    saveFile(entity);
    newFile(entity);
  } else if (Input::getKey(KeyCode::R) && Input::check(KeyCode::CTRL)) {
    deleteFile(entity);
    selectFile(entity);
  }
}
void FileSystem::upward(const Entity* entity) {
  if (_currentFile > 0) {
    saveFile(entity);
    _currentFile--;
    selectFile(entity);
  }
}
void FileSystem::downward(const Entity* entity) {
  if (_currentFile < static_cast<int>(entity->getComponent<DirectoryComponent>()->directory.size()) - 1) {
    saveFile(entity);
    _currentFile++;
    selectFile(entity);
  }
}
void FileSystem::deleteFile(const Entity* entity) {
  auto directory = entity->getComponent<DirectoryComponent>();
  FileUtility::removeRoom(_roomsPath + directory->directory[_currentFile]);
  directory->directory.erase(directory->directory.begin() + _currentFile);
  if (_currentFile > 0) _currentFile--;
}
void FileSystem::newFile(const Entity* entity) {
  auto roomStruct = getEntityManager()->getByTag("struct")[0];
  auto structure = EditorUtility::createEmptyStructure(roomStruct)->getComponent<StructureComponent>();

  auto directory = entity->getComponent<DirectoryComponent>();
  std::string name = readName(entity) + _fileExtension;
  FileUtility::saveRoom(_roomsPath + name, structure);
  directory->directory.emplace_back(name);

  _currentFile = static_cast<int>(directory->directory.size()) - 1;
}
void FileSystem::saveFile(const Entity* entity) {
  auto structure = getEntityManager()->getByTag("struct")[0]->getComponent<StructureComponent>();
  // TODO(AsTeFu): тестовый вариант, переделать
  if (_currentFile == -1) {
    entity->getComponent<DirectoryComponent>()->directory.emplace_back("room0.room");
    _currentFile = 1;
  }
  FileUtility::saveRoom(_roomsPath + entity->getComponent<DirectoryComponent>()->directory[_currentFile], structure);
}
void FileSystem::selectFile(const Entity* entity) const {
  auto structure = getEntityManager()->getByTag("struct")[0]->getComponent<StructureComponent>();
  FileUtility::readRoom(_roomsPath + entity->getComponent<DirectoryComponent>()->directory[_currentFile], structure);
}

void FileSystem::postUpdate(Entity* entity) {
  Terminal::setLayer(0);
  Terminal::crop(_position, _size);
  Terminal::clearArea(_position, _size);

  Terminal::setColor(Color::White);
  SceneRenderUtility::drawBorder(_position, _size);

  int leftMargin = 2;
  int topMargin = 2;
  int x = _position.getX() + leftMargin;
  int y = _position.getY() + topMargin;

  Terminal::print(x, y, "Saved rooms:");

  x += leftMargin * 2;
  y += topMargin;

  auto directory = entity->getComponent<DirectoryComponent>();

  // Тут крч магия, лучше сюда вообще не лезть, но оно работает
  int offset = std::max(0, _currentFile + _maxDisplayFile / 2 - static_cast<int>(directory->directory.size()));
  int start = std::max(0, _currentFile - _maxDisplayFile / 2 - offset);
  int end = std::min(start + _maxDisplayFile, static_cast<int>(directory->directory.size()));

  for (int i = start; i < end; ++i) {
    if (_currentFile == i) {
      Terminal::setColor(Color::White);
      drawCursor(x, y);
    } else {
      Terminal::setColor(Color::Gray);
    }

    Terminal::print(x, y++, directory->directory[i]);
  }

  drawHelp(x, y + 2);
}
void FileSystem::drawHelp(int x, int y) const {
  Terminal::setColor(Color::White);
  Terminal::print(x, y++, "New file - CTRL+N");
  Terminal::print(x, y++, "Save file - CTRL+S");
  Terminal::print(x, y++, "Remove file - CTRL+R");
  Terminal::print(x, y++, "Clear file - CTRL+C");
}
void FileSystem::drawCursor(int x, int y) const {
  Terminal::print(x - static_cast<int>(cursor.size()), y, cursor);
}

// TODO(AsTeFu): оочень большая функция
std::string FileSystem::readName(const Entity* directory) {
  std::string name;

  Vector2 position(20, 8);
  Vector2 size(40, 8);

  Terminal::setLayer(0);
  Terminal::clearArea(position, size);
  Terminal::setLayer(1);
  Terminal::clearArea(position, size);
  Terminal::setLayer(4);
  Terminal::clearArea(position, size);

  Terminal::setLayer(10);
  Terminal::setColor(Color::Yellow);
  SceneRenderUtility::drawBorder(position, size);

  int leftMargin = 5;
  int topMargin = 2;
  int x = position.getX() + leftMargin;
  int y = position.getY() + topMargin;

  Terminal::setColor(Color::White);
  std::string labelText = "Input file name: ";
  Terminal::print(x, y, labelText);

  do {
    name.clear();
    Terminal::setColor(Color::White);
    name = Terminal::readString(x + static_cast<int>(labelText.size()), y, 10);

    if (!isAvailableName(directory, name)) {
      Terminal::setColor(Color::Red);
      Terminal::print(x, y + 1, "Wrong name!");
      SceneRenderUtility::drawBorder(position, size);
    } else {
      break;
    }
  } while (true);
  Terminal::clear();

  return name;
}
bool FileSystem::isAvailableName(const Entity* directory, const string& name) {
  auto dir = directory->getComponent<DirectoryComponent>();

  if (StringUtility::trimCopy(name).empty()) return false;

  for (const auto& nameFile : dir->directory)
    if (StringUtility::split(nameFile, '.')[0] == name) return false;
  return true;
}
