//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_STEPSCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_STEPSCOMPONENT_H_

#include "ecs/IComponent.h"

class StepsComponent : public IComponent {
 public:
  int currentSteps;
  StepsComponent() : currentSteps(0) {}
  explicit StepsComponent(int steps) : currentSteps(steps) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_STEPSCOMPONENT_H_
