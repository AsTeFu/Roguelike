//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_ECS_ENTITY_H_
#define INCLUDE_ECS_ENTITY_H_

#include <map>
#include <memory>
#include <typeindex>
#include "ecs/IComponent.h"

using std::map;
using std::type_index;
using std::unique_ptr;

class Entity {
  friend class EntityManager;
  map<type_index, unique_ptr<IComponent>> _components;
  size_t _id = 0;

 public:
  explicit Entity(size_t id) : _id(id) {}

  template<typename Component, typename... Args>
  Entity* addComponent(Args&&... args) {
    _components[typeid(Component)] = std::make_unique<Component>(std::forward<Args>(args)...);
    return this;
  }

  template<typename Component>
  Component* getComponent() const {
    auto component = _components.at(typeid(Component)).get();
    return dynamic_cast<Component*>(component);
  }

  size_t getID() const {
    return _id;
  }

  template<typename Component>
  bool hasComponent() const {
    return _components.count(typeid(Component)) != 0;
  }
  template<typename Component>
  void removeComponent() {
    _components.erase(typeid(Component));
  }
  static Entity* copyEntity(Entity* const from, Entity* to) {
    for (auto& component : from->_components) {
      to->_components[component.first] = std::unique_ptr<IComponent>(component.second.get());
    }
    return to;
  }
};

#endif  // INCLUDE_ECS_ENTITY_H_
