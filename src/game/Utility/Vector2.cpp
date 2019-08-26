//
// Created by AsTeFu on 08.07.2019.
//

#include "game/Utility/Vector2.h"
#include <cmath>

Vector2 Vector2::LEFT = Vector2(-1, 0);
Vector2 Vector2::RIGHT = Vector2(1, 0);
Vector2 Vector2::UP = Vector2(0, -1);
Vector2 Vector2::DOWN = Vector2(0, 1);
Vector2 Vector2::ZERO = Vector2(0, 0);

int Vector2::getX() const {
  return _x;
}
int Vector2::getY() const {
  return _y;
}

void Vector2::setX(int newX) {
  _x = newX;
}
void Vector2::setY(int newY) {
  _y = newY;
}

void Vector2::translate(int dx, int dy) {
  _x += dx;
  _y += dy;
}
void Vector2::translate(const Vector2& dPos) {
  _x += dPos.getX();
  _y += dPos.getY();
}

void Vector2::set(const Vector2& vector) {
  setX(vector.getX());
  setY(vector.getY());
}
void Vector2::set(int x, int y) {
  setX(x);
  setY(y);
}
std::ostream& operator<<(std::ostream& os, const Vector2& vector2) {
  os << "(" << vector2.getX() << ", " << vector2.getY() << ")";
  return os;
}
bool Vector2::operator==(const Vector2& rhs) const {
  return getX() == rhs.getX() && getY() == rhs.getY();
}
bool Vector2::operator!=(const Vector2& rhs) const {
  return !(rhs == *this);
}
Vector2 Vector2::operator+(const Vector2& rhs) const {
  return {getX() + rhs.getX(), getY() + rhs.getY()};
}
Vector2 Vector2::operator-(const Vector2& rhs) const {
  return {getX() - rhs.getX(), getY() - rhs.getY()};
}

bool operator>(const Vector2& lhs, const Vector2& rhs) {
  if (lhs.getX() > rhs.getX())
    return true;
  else if (lhs.getX() < rhs.getX())
    return false;
  else
    return lhs.getY() > rhs.getY();
}
bool operator<(const Vector2& lhs, const Vector2& rhs) {
  return !(lhs > rhs);
}
Vector2 Vector2::operator+=(const Vector2& rhs) {
  _x += rhs.getX();
  _y += rhs.getY();
  return *this;
}
Vector2 Vector2::operator*(int c) const {
  return {getX() * c, getY() * c};
}
Vector2 Vector2::operator*=(int c) {
  _x *= c;
  _y *= c;
  return *this;
}
Vector2 Vector2::operator*(const Vector2& rhs) const {
  return {_x * rhs.getX(), _y * rhs.getY()};
}
Vector2 Vector2::operator*=(const Vector2& rhs) {
  _x *= rhs.getX();
  _y *= rhs.getY();
  return *this;
}
double Vector2::dotProd(const Vector2& rhs) const {
  return _x * rhs.getX() + _y * rhs.getY();
}
double Vector2::crossProd(const Vector2& rhs) const {
  return _x * rhs.getX() + _y * rhs.getY();
}
Vector2 Vector2::normalize() {
  auto len = magnitude();
  if (len <= 0.000000001) {
    _x = 0;
    _y = 0;
  } else {
    _x /= len;
    _y /= len;
  }

  return *this;
}
double Vector2::magnitude() const {
  return std::sqrt(_x * _x + _y * _y);
}
double Vector2::len2() const {
  return _x * _x + _y * _y;
}

Vector2 operator/(const Vector2& lhs, const int rhs) {
  return {lhs.getX() / rhs, lhs.getY() / rhs};
}
