//
// Created by AsTeFu on 30.08.2019.
//

#ifndef INCLUDE_UTILITIES_RANGE_H_
#define INCLUDE_UTILITIES_RANGE_H_

#include <ostream>
class Range {
 public:
  int minValue;
  int maxValue;
  Range(int min, int max) : minValue(min), maxValue(max) {}
  Range() : Range(0, 0) {}

  friend std::ostream& operator<<(std::ostream& os, const Range& range) {
    os << "(minValue: " << range.minValue << "; maxValue: " << range.maxValue << ")";
    return os;
  }
  bool operator==(const Range& rhs) const {
    return minValue == rhs.minValue && maxValue == rhs.maxValue;
  }
  bool operator!=(const Range& rhs) const {
    return !(rhs == *this);
  }
};

#endif  // INCLUDE_UTILITIES_RANGE_H_
