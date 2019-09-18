//
// Created by  on 18.09.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_LIGHTINGSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_LIGHTINGSYSTEM_H_

#include <game/Components/EnvironmentComponents/PointComponent.h>
#include <game/Components/EnvironmentComponents/WallComponent.h>
#include <map>
#include "ecs/ISystem.h"

class LightingSystem : public ISystem {
 private:
  std::map<int, Entity*> points;
  int width;

 protected:
  void postUpdate(Entity *entity) override;
  void update(Entity *entity) override;

 public:
  LightingSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                 SceneManager *const sceneManager, int width)
      : ISystem(entityManager, systemManager, sceneManager), width(width) {
    updateComponents();

    for (const auto &entity : _entities)
      if (entity->hasComponent<PointComponent>()) {
        auto transform = entity->getComponent<Transform>();
        points.emplace(transform->position.getX() + width * transform->position.getY(), entity);
      }
  }
  bool filter(Entity *entity) const override;
  bool brezenham(const Vector2 &start, const Vector2 &end) const;
  bool isVisibleWall(int x, int y) const;
  bool pickDot(int x, int y) const;
  void lightingProcess(const Entity *entity);
};

#endif  // INCLUDE_GAME_SYSTEMS_LIGHTINGSYSTEM_H_
