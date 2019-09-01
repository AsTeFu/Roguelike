//
// Created by AsTeFu on 20.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_ENHANCEDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_ENHANCEDTO_H_

#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include "game/Utility/DTO/ObjectDTO.h"

class EnhanceDTO : public ObjectDTO {
 public:
  SpecialComponent* specialComponent;
  AbilitiesComponent* abilitiesComponent;
  LevelComponent* levelComponent;
  HealthComponent* healthComponent;

  EnhanceDTO(SpecialComponent* specialComponent, AbilitiesComponent* abilitiesComponent, LevelComponent* levelComponent,
             HealthComponent* healthComponent)
      : specialComponent(specialComponent),
        abilitiesComponent(abilitiesComponent),
        levelComponent(levelComponent),
        healthComponent(healthComponent) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_ENHANCEDTO_H_
