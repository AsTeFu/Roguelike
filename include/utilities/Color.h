//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_UTILITIES_COLOR_H_
#define INCLUDE_UTILITIES_COLOR_H_

#include <ostream>

class Color {
 public:
  int a;
  int r;
  int g;
  int b;
  Color(int a, int r, int g, int b) : a(a), r(r), g(g), b(b) {}
  Color() : Color(0, 0, 0, 0) {}

  friend std::ostream& operator<<(std::ostream& os, const Color& argb) {
    os << "(a: " << argb.a << "; r: " << argb.r << "; g: " << argb.g << "; b: " << argb.b << ")";
    return os;
  }
  bool operator==(const Color& rhs) const {
    return a == rhs.a && r == rhs.r && g == rhs.g && b == rhs.b;
  }
  bool operator!=(const Color& rhs) const {
    return !(rhs == *this);
  }

  static Color White;
  static Color Gray;
  static Color Green;
  static Color Yellow;
  static Color Red;
};

#endif  // INCLUDE_UTILITIES_COLOR_H_
