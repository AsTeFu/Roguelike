//
// Created by AsTeFu on 19.08.2019.
//

#include "game/Systems/ShopOpenSystem.h"
#include <ecs/EntityManager.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/EnvironmentComponents/ShopComponent.h>
#include <game/Utility/DTO/ShopDTO.h>
#include <game/Utility/Input.h>

bool ShopOpenSystem::filter(Entity* entity) const {
  return entity->hasComponent<ShopComponent>() && entity->hasComponent<Transform>();
}
void ShopOpenSystem::update(Entity* entity) {
  auto player = getEntityManager()->getByTag("player")[0];
  auto shop = entity->getComponent<ShopComponent>();

  if (Input::getKey(KeyCode::Enter) &&
      player->getComponent<Transform>()->position == entity->getComponent<Transform>()->position) {
    getSceneManager()->getContext()->addObject<ShopDTO>(
        shop, player->getComponent<WeaponComponent>(), player->getComponent<ArmorComponent>(),
        player->getComponent<WalletComponent>(), player->getComponent<StarvationComponent>(),
        player->getComponent<HealthComponent>(), player->getComponent<InventoryComponent>(),
        player->getComponent<SpecialComponent>());
    getSceneManager()->switchScene("Shop");
  }
}
