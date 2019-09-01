//
// Created by  on 06.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_WALLETCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_WALLETCOMPONENT_H_

#include "ecs/IComponent.h"

class WalletComponent : public IComponent {
 public:
  int cash;
  explicit WalletComponent(int startCash) : cash(startCash) {}
  WalletComponent() : cash(0) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_WALLETCOMPONENT_H_
