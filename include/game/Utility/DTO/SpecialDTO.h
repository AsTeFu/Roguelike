//
// Created by AsTeFu on 10.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_SPECIALDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_SPECIALDTO_H_

#include <map>
#include <string>
#include <utility>
#include "game/Utility/DTO/ObjectDTO.h"

class SpecialDTO : public ObjectDTO {
 public:
  Special special;
  explicit SpecialDTO(Special  special) : special(std::move(special)) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_SPECIALDTO_H_
