//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_UTILITIES_STRINGUTILITY_H_
#define INCLUDE_UTILITIES_STRINGUTILITY_H_

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

class StringUtility {
 public:
  static std::vector<std::string> split(const std::string& str, char reg) {
    std::stringstream ss(str);
    std::string line;
    std::vector<std::string> strings;

    while (std::getline(ss, line, reg)) {
      strings.push_back(std::move(line));
    }

    return strings;
  }
  static void trimBegin(std::string* str) {
    str->erase(str->begin(), std::find_if(str->begin(), str->end(), [](int ch) { return !std::isspace(ch); }));
  }
  static void trimEnd(std::string* str) {
    str->erase(std::find_if(str->rbegin(), str->rend(), [](int ch) { return !std::isspace(ch); }).base(), str->end());
  }
  static void trim(std::string* str) {
    trimBegin(str);
    trimEnd(str);
  }
  static std::string trimBeginCopy(std::string str) {
    trimBegin(&str);
    return str;
  }
  static std::string trimEndCopy(std::string str) {
    trimEnd(&str);
    return str;
  }
  static std::string trimCopy(std::string str) {
    trim(&str);
    return str;
  }
  static std::string toUpper(const std::string& str) {
    std::string tmp;
    for (const auto& symbol : str) tmp.push_back(toupper(symbol));
    return tmp;
  }
};

#endif  // INCLUDE_UTILITIES_STRINGUTILITY_H_
