//
// Created by AsTeFu on 01.09.2019.
//

#include <utilities/KeyCode.h>

KeyCode::KeyCode(int key) : key(key) {}

KeyCode KeyCode::A(0x04);
KeyCode KeyCode::B(0x05);
KeyCode KeyCode::C(0x06);
KeyCode KeyCode::D(0x07);
KeyCode KeyCode::E(0x08);
KeyCode KeyCode::F(0x09);
KeyCode KeyCode::G(0x0A);
KeyCode KeyCode::H(0x0B);
KeyCode KeyCode::I(0x0C);
KeyCode KeyCode::J(0x0D);
KeyCode KeyCode::K(0x0E);
KeyCode KeyCode::L(0x0F);
KeyCode KeyCode::M(0x10);
KeyCode KeyCode::N(0x11);
KeyCode KeyCode::O(0x12);
KeyCode KeyCode::P(0x13);
KeyCode KeyCode::Q(0x14);
KeyCode KeyCode::R(0x15);
KeyCode KeyCode::S(0x16);
KeyCode KeyCode::T(0x17);
KeyCode KeyCode::U(0x18);
KeyCode KeyCode::V(0x19);
KeyCode KeyCode::W(0x1A);
KeyCode KeyCode::X(0x1B);
KeyCode KeyCode::Y(0x1C);
KeyCode KeyCode::Z(0x1D);
KeyCode KeyCode::ALPHA1(0x1E);
KeyCode KeyCode::ALPHA2(0x1F);
KeyCode KeyCode::ALPHA3(0x20);
KeyCode KeyCode::ALPHA4(0x21);
KeyCode KeyCode::ALPHA5(0x22);
KeyCode KeyCode::ALPHA6(0x23);
KeyCode KeyCode::ALPHA7(0x24);
KeyCode KeyCode::ALPHA8(0x25);
KeyCode KeyCode::ALPHA9(0x26);
KeyCode KeyCode::ALPHA0(0x27);
KeyCode KeyCode::RETURN(0x28);
KeyCode KeyCode::Enter(0x28);
KeyCode KeyCode::Escape(0x29);
KeyCode KeyCode::BACKSPACE(0x2A);
KeyCode KeyCode::TAB(0x2B);
KeyCode KeyCode::Space(0x2C);
KeyCode KeyCode::MINUS(0x2D);
KeyCode KeyCode::EQUALS(0x2E);
KeyCode KeyCode::LBRACKET(0x2F);
KeyCode KeyCode::RBRACKET(0x30);
KeyCode KeyCode::BACKSLASH(0x31);
KeyCode KeyCode::SEMICOLON(0x33);
KeyCode KeyCode::APOSTROPHE(0x34);
KeyCode KeyCode::GRAVE(0x35);
KeyCode KeyCode::COMMA(0x36);
KeyCode KeyCode::PERIOD(0x37);
KeyCode KeyCode::SLASH(0x38);
KeyCode KeyCode::F1(0x3A);
KeyCode KeyCode::F2(0x3B);
KeyCode KeyCode::F3(0x3C);
KeyCode KeyCode::F4(0x3D);
KeyCode KeyCode::F5(0x3E);
KeyCode KeyCode::F6(0x3F);
KeyCode KeyCode::F7(0x40);
KeyCode KeyCode::F8(0x41);
KeyCode KeyCode::F9(0x42);
KeyCode KeyCode::F10(0x43);
KeyCode KeyCode::F11(0x44);
KeyCode KeyCode::F12(0x45);
KeyCode KeyCode::PAUSE(0x48);
KeyCode KeyCode::INSERT(0x49);
KeyCode KeyCode::HOME(0x4A);
KeyCode KeyCode::PAGEUP(0x4B);
KeyCode KeyCode::DELETE(0x4C);
KeyCode KeyCode::END(0x4D);
KeyCode KeyCode::PAGEDOWN(0x4E);
KeyCode KeyCode::RightArrow(0x4F);
KeyCode KeyCode::LeftArrow(0x50);
KeyCode KeyCode::DownArrow(0x51);
KeyCode KeyCode::UpArrow(0x52);
KeyCode KeyCode::KP_DIVIDE(0x54);
KeyCode KeyCode::KP_MULTIPLY(0x55);
KeyCode KeyCode::KP_MINUS(0x56);
KeyCode KeyCode::KP_PLUS(0x57);
KeyCode KeyCode::KP_ENTER(0x58);
KeyCode KeyCode::KP_1(0x59);
KeyCode KeyCode::KP_2(0x5A);
KeyCode KeyCode::KP_3(0x5B);
KeyCode KeyCode::KP_4(0x5C);
KeyCode KeyCode::KP_5(0x5D);
KeyCode KeyCode::KP_6(0x5E);
KeyCode KeyCode::KP_7(0x5F);
KeyCode KeyCode::KP_8(0x60);
KeyCode KeyCode::KP_9(0x61);
KeyCode KeyCode::KP_0(0x62);
KeyCode KeyCode::KP_PERIOD(0x63);
KeyCode KeyCode::SHIFT(0x70);
KeyCode KeyCode::CONTROL(0x71);
KeyCode KeyCode::ALT(0x72);
KeyCode KeyCode::Close(0xE0);

bool KeyCode::operator<(const KeyCode& rhs) const {
  return key < rhs.key;
}
bool KeyCode::operator>(const KeyCode& rhs) const {
  return rhs < *this;
}
bool KeyCode::operator<=(const KeyCode& rhs) const {
  return !(rhs < *this);
}
bool KeyCode::operator>=(const KeyCode& rhs) const {
  return !(*this < rhs);
}
