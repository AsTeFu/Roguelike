//
// Created by AsTeFu on 10.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_CHESTDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_CHESTDTO_H_

#include <ecs/Entity.h>
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <iostream>
#include "game/Utility/DTO/ObjectDTO.h"

class ChestDTO : public ObjectDTO {
 public:
  Entity* player;
  ChestComponent* chestComponent;
  ChestDTO(Entity* entity, ChestComponent* chestComponent) : player(entity), chestComponent(chestComponent) {
    if (!player->hasComponent<PlayerComponent>()) std::cout << "ChestDTO: incorrect player" << std::endl;
  }

  template<typename Component>
  Component* getComponent() {
    return player->getComponent<Component>();
  }
};

#endif  // INCLUDE_GAME_UTILITY_DTO_CHESTDTO_H_
