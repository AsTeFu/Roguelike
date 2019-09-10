//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_SYSTEMS_FILESYSTEM_H_
#define INCLUDE_EDITOR_SYSTEMS_FILESYSTEM_H_

#include <editor/Components/FileNameComponent.h>
#include <string>
#include <utility>
#include "ecs/ISystem.h"

class FileSystem : public ISystem {
 private:
  Vector2 _position;
  Vector2 _size;
  std::string cursor{"=>"};
  int _currentFile{};
  int _maxDisplayFile{10};
  const std::string _roomsPath;
  const std::string _fileExtension = {".room"};

  void selectFile(const Entity *entity) const;
  void saveFile(const Entity *entity);
  void newFile(const Entity *entity);
  void deleteFile(const Entity *entity);

  static std::string readName(const Entity *directory);
  static bool isAvailableName(const Entity *directory, const string &name);
  void downward(const Entity *entity);
  void upward(const Entity *entity);
  void drawCursor(int x, int y) const;
  void drawHelp(int x, int y) const;

 protected:
  void update(Entity *entity) override;
  void postUpdate(Entity *entity) override;

 public:
  FileSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager,
             const Vector2 &position, std::string path);
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_EDITOR_SYSTEMS_FILESYSTEM_H_
