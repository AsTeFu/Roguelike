//
// Created by AsTeFu on 01.09.2019.
//

#ifndef INCLUDE_UTILITIES_KEYCODE_H_
#define INCLUDE_UTILITIES_KEYCODE_H_

class KeyCode {
 public:
  int key;
  bool operator<(const KeyCode& rhs) const;
  bool operator>(const KeyCode& rhs) const;
  bool operator<=(const KeyCode& rhs) const;
  bool operator>=(const KeyCode& rhs) const;

  explicit KeyCode(int key);

  static KeyCode A;
  static KeyCode B;
  static KeyCode C;
  static KeyCode D;
  static KeyCode E;
  static KeyCode F;
  static KeyCode G;
  static KeyCode H;
  static KeyCode I;
  static KeyCode J;
  static KeyCode K;
  static KeyCode L;
  static KeyCode M;
  static KeyCode N;
  static KeyCode O;
  static KeyCode P;
  static KeyCode Q;
  static KeyCode R;
  static KeyCode S;
  static KeyCode T;
  static KeyCode U;
  static KeyCode V;
  static KeyCode W;
  static KeyCode X;
  static KeyCode Y;
  static KeyCode Z;
  static KeyCode ALPHA1;
  static KeyCode ALPHA2;
  static KeyCode ALPHA3;
  static KeyCode ALPHA4;
  static KeyCode ALPHA5;
  static KeyCode ALPHA6;
  static KeyCode ALPHA7;
  static KeyCode ALPHA8;
  static KeyCode ALPHA9;
  static KeyCode ALPHA0;
  static KeyCode RETURN;
  static KeyCode Enter;
  static KeyCode Escape;
  static KeyCode BACKSPACE;
  static KeyCode TAB;
  static KeyCode Space;
  static KeyCode MINUS;
  static KeyCode EQUALS;
  static KeyCode LBRACKET;
  static KeyCode RBRACKET;
  static KeyCode BACKSLASH;
  static KeyCode SEMICOLON;
  static KeyCode APOSTROPHE;
  static KeyCode GRAVE;
  static KeyCode COMMA;
  static KeyCode PERIOD;
  static KeyCode SLASH;
  static KeyCode F1;
  static KeyCode F2;
  static KeyCode F3;
  static KeyCode F4;
  static KeyCode F5;
  static KeyCode F6;
  static KeyCode F7;
  static KeyCode F8;
  static KeyCode F9;
  static KeyCode F10;
  static KeyCode F11;
  static KeyCode F12;
  static KeyCode PAUSE;
  static KeyCode INSERT;
  static KeyCode HOME;
  static KeyCode PAGEUP;
  static KeyCode DELETE;
  static KeyCode END;
  static KeyCode PAGEDOWN;
  static KeyCode RightArrow;
  static KeyCode LeftArrow;
  static KeyCode DownArrow;
  static KeyCode UpArrow;
  static KeyCode KP_DIVIDE;
  static KeyCode KP_MULTIPLY;
  static KeyCode KP_MINUS;
  static KeyCode KP_PLUS;
  static KeyCode KP_ENTER;
  static KeyCode KP_1;
  static KeyCode KP_2;
  static KeyCode KP_3;
  static KeyCode KP_4;
  static KeyCode KP_5;
  static KeyCode KP_6;
  static KeyCode KP_7;
  static KeyCode KP_8;
  static KeyCode KP_9;
  static KeyCode KP_0;
  static KeyCode KP_PERIOD;
  static KeyCode SHIFT;
  static KeyCode CTRL;
  static KeyCode ALT;
  static KeyCode Close;
};

#endif  // INCLUDE_UTILITIES_KEYCODE_H_
