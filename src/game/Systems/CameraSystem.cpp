//
// Created by AsTeFu on 03.08.2019.
//

#include "game/Systems/CameraSystem.h"
#include <game/Components/BaseComponent/Graphic.h>
#include "ecs/EntityManager.h"
#include "game/Components/BaseComponent/CameraComponent.h"
#include "game/Components/BaseComponent/Movement.h"
#include "game/Components/BaseComponent/Transform.h"
#include "utilities/MathUtility.h"

bool CameraSystem::filter(Entity* entity) const {
  return entity->hasComponent<CameraComponent>() && entity->hasComponent<Transform>();
}

int norm(int num) {
  if (num == 0) return 0;
  if (num > 0) return 1;
  return -1;
}

void CameraSystem::update(Entity* entity) {
  auto camera = entity->getComponent<CameraComponent>();
  auto transform = entity->getComponent<Transform>();
  auto target = getEntityManager()->getByTag("player")[0]->getComponent<Transform>();

  int lengthX = transform->position.getX() - target->position.getX();
  int lengthY = transform->position.getY() - target->position.getY();

  // std::cout << "CameraPos: " << transform->positionShop << "; TargetPos: " << target->positionShop << ";"
  //          << "Length: " << Vector2(lengthX, lengthY) << std::endl;

  if (abs(lengthX) > camera->border.getX()) {
    transform->position.setX(transform->position.getX() - norm(lengthX));
  }
  if (abs(lengthY) > camera->border.getY()) transform->position.setY(transform->position.getY() - norm(lengthY));

  camera->offset.set(camera->size.getX() - transform->position.getX(),
                     camera->size.getY() - transform->position.getY());

  for (const auto& graphic : *getEntityManager()) {
    if (graphic.hasComponent<Graphic>()) {
      graphic.getComponent<Graphic>()->offset.set(camera->offset);
    }
  }
}
