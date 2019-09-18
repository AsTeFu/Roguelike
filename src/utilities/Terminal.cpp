//
// Created by AsTeFu on 31.08.2019.
//

#include <BearLibTerminal.h>
#include <utilities/StringUtility.h>
#include <utilities/Terminal.h>
#include <string>

void Terminal::setColor(Color color) {
  terminal_color(color_from_argb(color.a, color.r, color.g, color.b));
}
void Terminal::clearArea(const Vector2& position, const Vector2& size) {
  clearArea(position.getX(), position.getY(), size.getX(), size.getY());
}
void Terminal::clearArea(int x, int y, int w, int h) {
  terminal_clear_area(x, y, w, h);
}
void Terminal::setLayer(int layer) {
  terminal_layer(layer);
}
void Terminal::put(int x, int y, int symbol) {
  terminal_put(x, y, symbol);
}
void Terminal::put(const Vector2& position, int symbol) {
  put(position.getX(), position.getY(), symbol);
}
void Terminal::print(const Vector2& position, const std::string& str) {
  print(position.getX(), position.getY(), str);
}
void Terminal::print(int x, int y, const std::string& str) {
  terminal_print(x, y, str.c_str());
}
void Terminal::printf(int x, int y, const char* str, ...) {
  va_list params;
  va_start(params, str);
  terminal_printf(x, y, terminal_vsprintf(str, params));
  va_end(params);
}
void Terminal::printf(const Vector2& position, const char* str, ...) {
  va_list params;
  va_start(params, str);
  terminal_printf(position.getX(), position.getY(), terminal_vsprintf(str, params));
  va_end(params);
}
void Terminal::clear() {
  terminal_clear();
}
Color Terminal::pickColor(int x, int y, int index) {
  // TODO(ATF): ок, это не работает, я не понял
  color_t colort = terminal_pick_color(x, y, index);
  int a, r, g, b;

  if (colort == 0) return Color(0, 0, 0, 0);

  a = colort >> 6;

  r = colort >> 4;
  r = r << 2;

  g = colort >> 2;
  g = g << 4;

  b = colort << 6;
  return Color(a, r, g, b);
}
Tile Terminal::pick(int x, int y, int index) {
  return Tile(terminal_pick(x, y, index), pickColor(x, y, index));
}
void Terminal::start() {
  terminal_open();
}
void Terminal::refresh() {
  terminal_refresh();
}
void Terminal::crop(int x, int y, int w, int h) {
  terminal_crop(x, y, w, h);
}
void Terminal::crop(const Vector2& position, const Vector2& size) {
  crop(position.getX(), position.getY(), size.getX(), size.getY());
}
void Terminal::close() {
  terminal_close();
}
std::string Terminal::readString(int x, int y, int max) {
  std::string str;
  while (true) {
    int key = terminal_read();

    if (key == TK_RETURN || key == TK_ESCAPE || key == TK_CLOSE) {
      break;
    } else if (key == TK_BACKSPACE && !str.empty()) {
      str.resize(str.length() - 1);
    } else if (terminal_check(TK_CHAR) && static_cast<int>(str.length()) < max) {
      int symbol = terminal_state(TK_CHAR);
      if (StringUtility::isAvailableSymbol(symbol)) str.push_back(terminal_state(TK_CHAR));
    }

    clearArea(x, y, max + 1, 1);
    printf(x, y, "%s_", str.c_str());
    refresh();
  }

  return str;
}

std::string Terminal::readString(const Vector2& position, int max) {
  return readString(position.getX(), position.getY(), max);
}
Color Terminal::pickColor(const Vector2& position, int index) {
  return pickColor(position.getX(), position.getY(), index);
}
void Terminal::enableMouse() {
  terminal_set("input.mouse-cursor = true");
}
void Terminal::put(const Vector2& position, const Tile& tile) {
  put(position.getX(), position.getY(), tile);
}
void Terminal::put(int x, int y, const Tile& tile) {
  setColor(tile.color);
  put(x, y, tile.graphic);
}
