//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_SYSTEMS_STRUCTURESYSTEM_H_
#define INCLUDE_EDITOR_SYSTEMS_STRUCTURESYSTEM_H_

#include "ecs/ISystem.h"

class StructureSystem : public ISystem {
 private:
  Vector2 _position;
  int _left = 5;
  int _top = 4;

  Vector2 getMousePosition() const;
  bool isActiveTable(const Vector2 &point, const Vector2 &sizeTable) const;

  void drawEmptyTile(const Entity *entity);
  void drawTile(const Vector2 &mousePosition, StructureComponent *structure);

 protected:
  void update(Entity *entity) override;
  void postUpdate(Entity *entity) override;

 public:
  StructureSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                  SceneManager *const sceneManager, const Vector2 &position)
      : ISystem(entityManager, systemManager, sceneManager), _position(position) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_EDITOR_SYSTEMS_STRUCTURESYSTEM_H_
