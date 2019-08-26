//
// Created by AsTeFu on 20.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_ENHANCEDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_ENHANCEDTO_H_

#include <game/Components/AbilitiesComponent.h>
#include <game/Components/HealthComponent.h>
#include <game/Components/LevelComponent.h>
#include <game/Components/SpecialComponent.h>
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
