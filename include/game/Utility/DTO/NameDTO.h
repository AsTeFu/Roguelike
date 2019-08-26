//
// Created by AsTeFu on 11.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_NAMEDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_NAMEDTO_H_

#include <string>
#include <utility>
#include "game/Utility/DTO/ObjectDTO.h"

class NameDTO : public ObjectDTO {
 public:
  const std::string name;
  explicit NameDTO(char* name) : name(name) {}
  explicit NameDTO(std::string name) : name(std::move(name)) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_NAMEDTO_H_
