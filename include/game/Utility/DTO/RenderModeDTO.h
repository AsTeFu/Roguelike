//
// Created by AsTeFu on 18.09.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_RENDERMODEDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_RENDERMODEDTO_H_

#include "game/Utility/DTO/ObjectDTO.h"

class RenderModeDTO : public ObjectDTO {
 public:
  bool mode;
  explicit RenderModeDTO(bool mode) : mode(mode) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_RENDERMODEDTO_H_
