//
// Created by AsTeFu on 09.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_PLAYERDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_PLAYERDTO_H_

#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include <game/Utility/DTO/ObjectDTO.h>
#include <string>
#include <utility>

class PlayerDTO : public ObjectDTO {
 public:
  Entity* player;
  explicit PlayerDTO(Entity* player) : player(player) {}

  template<typename Component>
  Component* getComponent() {
    return player->getComponent<Component>();
  }
};

#endif  // INCLUDE_GAME_UTILITY_DTO_PLAYERDTO_H_
