//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_SYSTEMS_STRUCTURESYSTEM_H_
#define INCLUDE_ROOMCREATOR_SYSTEMS_STRUCTURESYSTEM_H_

#include "ecs/ISystem.h"

class StructureSystem : public ISystem {
 private:
  Vector2 _position;
  int _left = 5;
  int _top = 4;

  Vector2 linePos{-1, -1};

  Vector2 getMousePosition() const;
  bool isActiveTable(const Vector2 &point, const Vector2 &sizeTable) const;

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
  void brezenham(StructureComponent *structire, const Vector2 &start, const Vector2 &end) const;
  void brezenhamPosible(StructureComponent *structure, const Vector2 &start, const Vector2 &end) const;
};

#endif  // INCLUDE_ROOMCREATOR_SYSTEMS_STRUCTURESYSTEM_H_
