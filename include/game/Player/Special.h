//
// Created by AsTeFu on 26.07.2019.
//

#ifndef INCLUDE_GAME_PLAYER_SPECIAL_H_
#define INCLUDE_GAME_PLAYER_SPECIAL_H_

#include <utilities/Range.h>
#include <map>
#include <string>

using std::map;
using std::string;

enum StatSpecial { STRENGTH = 0, PERCEPTION, ENDURANCE, CHARISMA, INTELLIGENCE, AGILITY, LUCK };

class Special {
 private:
  int _minValue;
  int _maxValue;

  int _startPoints;
  int _currentPoints;

  map<string, int> _stats;

 public:
  Special(int minValue, int maxValue, int startPoints);
  Special(const Range& range, int startPoints);
  bool addPoint(const string& stat);
  int addPoints(const string& stat, int points);
  bool addPoint(StatSpecial stat);
  int addPoints(StatSpecial stat, int points);
  bool removePoint(const string& stat);
  int removePoints(const string& stat, int points);
  void addPoints(const std::map<std::string, int>& effects);
  void removePoints(const std::map<std::string, int>& effects);
  void clear();
  int getValue(const string& stat) const;
  int getValue(StatSpecial stat) const;
  int size() const;
  int countPoints() const;
  const map<string, int>& getStats() const;
  void addAvailablePoint();
  void addAvailablePoints(int value);
};

#endif  // INCLUDE_GAME_PLAYER_SPECIAL_H_
