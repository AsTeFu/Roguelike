//
// Created by AsTeFu on 26.07.2019.
//

#ifndef INCLUDE_GAME_PLAYER_SPECIAL_H_
#define INCLUDE_GAME_PLAYER_SPECIAL_H_

#include <map>
#include <string>

using std::map;
using std::string;

enum StatSpecial { STRENGTH = 0, PERCEPTION, ENDURANCE, CHARISMA, INTELLIGENCE, AGILITY, LUCK };

class Special {
 private:
  int _minValue = 1;
  int _maxValue = 10;
  int _startPoints = 40;
  int _currentPoints;

  map<string, int> _stats;  // = {{"strength", 0},     {"perception", 0}, {"endurance", 0}, {"charisma", 0},
                            //  {"intelligence", 0}, {"agility", 0},    {"luck", 0}};

  // (Сила) - урон, уровень брони, степень брони
  // (Восприятие) - видимость??? (сделать ограничение видимости)
  // (Выносливость) - объем инвенторя
  // (Харизма) - цены в магазине
  // (Интеллект) - способности или маг урон
  // (Ловкость) - уклонение
  // (Удача) - шанс найти классные вещи в сундуках

 public:
  Special(int minValue, int maxValue, int startPoints);
  bool addPoint(const string& stat);
  int addPoints(const string& stat, int points);
  bool addPoint(StatSpecial stat);
  int addPoints(StatSpecial stat, int points);
  bool removePoint(const string& stat);
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
