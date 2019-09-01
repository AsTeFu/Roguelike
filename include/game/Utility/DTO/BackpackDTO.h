//
// Created by AsTeFu on 11.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_BACKPACKDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_BACKPACKDTO_H_

#include <ecs/Entity.h>
#include <game/Components/ItemComponents/ArmorComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include "game/Utility/DTO/ObjectDTO.h"

class BackpackDTO : public ObjectDTO {
 public:
  Entity* player;

  explicit BackpackDTO(Entity* player) : player(player) {
    if (!player->hasComponent<PlayerComponent>()) std::cout << "Backpack: player incorrect!" << std::endl;
  }

  template<typename Component>
  Component* getComponent() {
    return player->getComponent<Component>();
  }
};

#endif  // INCLUDE_GAME_UTILITY_DTO_BACKPACKDTO_H_
