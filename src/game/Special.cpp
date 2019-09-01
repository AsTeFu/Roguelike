//
// Created by AsTeFu on 26.07.2019.
//

#include "game/Player/Special.h"

#include <map>
#include <string>
#include "game/Utility/Config.h"

bool Special::addPoint(const string& stat) {
  if (_stats[stat] == _maxValue || _currentPoints == 0) return false;
  _stats[stat]++;
  _currentPoints--;
  return true;
}
bool Special::addPoint(StatSpecial stat) {
  return addPoint(Config::getInstance().statsSpecial[stat]);
}
Special::Special(int minValue, int maxValue, int startPoints)
    : _minValue(minValue), _maxValue(maxValue), _startPoints(startPoints), _currentPoints(startPoints) {
  for (const auto& stat : Config::getInstance().statsSpecial) {
    _stats[stat] = 0;

    for (int i = 0; i < minValue; i++) addPoint(stat);
  }
}
Special::Special(const Range& range, int startPoints) : Special(range.minValue, range.maxValue, startPoints) {}
bool Special::removePoint(const string& stat) {
  if (_stats[stat] == _minValue) return false;
  _stats[stat]--;
  _currentPoints++;
  return true;
}
int Special::getValue(const string& stat) const {
  return _stats.at(stat);
}
int Special::size() const {
  return _stats.size();
}
int Special::countPoints() const {
  return _currentPoints;
}
int Special::getValue(StatSpecial stat) const {
  return _stats.at(Config::getInstance().statsSpecial[stat]);
}
const map<string, int>& Special::getStats() const {
  return _stats;
}
void Special::clear() {
  for (const auto& stat : _stats) {
    while (removePoint(stat.first)) {
    }
  }
}
void Special::addAvailablePoint() {
  _maxValue++;
  _currentPoints++;
}
void Special::addAvailablePoints(int value) {
  _maxValue += value;
  _currentPoints += value;
}
int Special::addPoints(const string& stat, int points) {
  for (int i = 0; i < points; i++) {
    if (!addPoint(stat)) return points - i;
  }
  return 0;
}
int Special::addPoints(StatSpecial stat, int points) {
  for (int i = 0; i < points; i++)
    if (!addPoint(stat)) return points - i;
  return 0;
}
int Special::removePoints(const string& stat, int points) {
  for (int i = 0; i < points; ++i)
    if (!removePoint(stat)) return points - i;
  return 0;
}
void Special::addPoints(const std::map<std::string, int>& effects) {
  for (const auto& effect : effects) addPoints(effect.first, effect.second);
}
void Special::removePoints(const std::map<std::string, int>& effects) {
  for (const auto& effect : effects) removePoints(effect.first, effect.second);
}
