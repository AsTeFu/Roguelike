//
// Created by AsTeFu on 17.09.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_IRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_IRENDERSYSTEM_H_

class IRenderSystem {
 public:
  virtual void render(Entity* entity) = 0;
  virtual void start() {}
  virtual void end() {}
  // virtual void renderWall(Entity* entity) = 0;
  virtual ~IRenderSystem() = default;
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_IRENDERSYSTEM_H_
