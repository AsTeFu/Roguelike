//
// Created by  on 16.09.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_TEXTRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_TEXTRENDERSYSTEM_H_

#include "ecs/ISystem.h"
#include "game/Systems/RenderSystems/IRenderSystem.h"

class TextRenderSystem : public IRenderSystem {
 private:
  EntityManager *entityManager;

  bool brezenham(const Vector2 &start, const Vector2 &end) const;
  bool getLighting(Entity *entity, Transform *playerTransform) const;
  bool pickDot(int x, int y) const;
  bool isVisibleWall(int x, int y) const;

 protected:
  void render(Entity *entity) override;
  // void renderWall(Entity *entity) override;

 public:
  explicit TextRenderSystem(EntityManager *const entityManager) : entityManager(entityManager) {}
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_TEXTRENDERSYSTEM_H_
