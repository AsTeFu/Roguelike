//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_ECS_ENTITYMANAGER_H_
#define INCLUDE_ECS_ENTITYMANAGER_H_

#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "ecs/Entity.h"

using std::map;
using std::string;
using std::vector;
using std::unique_ptr;

class EntityManager {
 private:
  map<size_t, unique_ptr<Entity>> _entities;
  map<string, vector<Entity*>> _entitiesByTag;
  size_t _lastEntityID = 1;

 public:
  Entity* createEntity();
  Entity* createEntity(const string& tag);
  EntityManager* deleteEntity(size_t id);
  EntityManager* deleteAll();

  Entity* getByID(size_t id) const;
  vector<Entity*> getByTag(const string& tag) const;
  bool isTag(const string& tag) const;

  template<typename Functor>
  void ForEach(const Functor& func) {
    for (auto& entity : _entities) {
      func(entity.second.get());
    }
  }
  class Iterator {
    std::map<size_t, std::unique_ptr<Entity>>::iterator iterator_;

   public:
    explicit Iterator(const std::map<size_t, std::unique_ptr<Entity>>::iterator& iterator) : iterator_(iterator) {}

    Iterator operator++() {
      iterator_.operator++();
      return *this;
    }
    Iterator operator++(int step) {
      iterator_.operator++(step);
      return *this;
    }

    Entity& operator*() {
      return *iterator_.operator*().second;
    }

    Entity* operator->() {
      return iterator_.operator*().second.get();
    }

    bool operator==(const Iterator& rhs) {
      return iterator_ == rhs.iterator_;
    }
    bool operator!=(const Iterator& rhs) {
      return iterator_ != rhs.iterator_;
    }
  };

  Iterator begin() {
    return Iterator{_entities.begin()};
  }

  Iterator end() {
    return Iterator{_entities.end()};
  }
  void deleteTag(const string& tag);
};

#endif  // INCLUDE_ECS_ENTITYMANAGER_H_
