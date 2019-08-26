//
// Created by AsTeFu on 08.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_VECTOR2_H_
#define INCLUDE_GAME_UTILITY_VECTOR2_H_

#include <cmath>
#include <iostream>

class Vector2 {
 private:
  int _x;
  int _y;

 public:
  Vector2() : _x(0), _y(0) {}
  Vector2(int x, int y) : _x(x), _y(y) {}

  static Vector2 LEFT;
  static Vector2 RIGHT;
  static Vector2 DOWN;
  static Vector2 UP;
  static Vector2 ZERO;

  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  void set(int x, int y);
  void set(const Vector2& vector2);

  void translate(int dx, int dy);
  void translate(const Vector2& dPos);

  friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2);
  bool operator==(const Vector2& rhs) const;
  bool operator!=(const Vector2& rhs) const;
  Vector2 operator+(const Vector2& rhs) const;
  Vector2 operator+=(const Vector2& rhs);
  Vector2 operator-(const Vector2& rhs) const;
  Vector2 operator*(int c) const;
  Vector2 operator*=(int c);
  Vector2 operator*(const Vector2& rhs) const;
  Vector2 operator*=(const Vector2& rhs);
  double dotProd(const Vector2& rhs) const;
  double crossProd(const Vector2& rhs) const;
  double magnitude() const;
  Vector2 normalize();
  friend bool operator>(const Vector2& lhs, const Vector2& rhs);
  friend bool operator<(const Vector2& lhs, const Vector2& rhs);
  double len2() const;
};

#endif  // INCLUDE_GAME_UTILITY_VECTOR2_H_
