//
// Created by AsTeFu on 16.07.2019.
//

#include "game/Scenes/EndGameScene.h"
#include <game/RoomManager/Room.h>
#include <utilities/Terminal.h>
#include <algorithm>
#include <fstream>
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/Input.h"

void EndGameScene::render() {
  Vector2 size(Config::getInstance().sizeTerminal.getX() - 20, 4);
  Vector2 position(10, 3);

  /*
  Terminal::setLayer(12);
  // terminal_clear();
  // terminal_color(color_from_argb(255, 255, 255, 255));

  // drawHeader(position, size, "THE END");

  int offsetX = position.getX() + 3;
  int offsetY = position.getY() + size.getY() + 2;

  // terminal_printf(offsetX, offsetY++, "Rooms:        %d", Room::countRoom);
  offsetY += 1;

  // terminal_printf(offsetX, offsetY++, "Name:         %s", player->name.c_str());
  // terminal_printf(offsetX, offsetY++, "Cash:         %d", player->cash);
  // terminal_printf(offsetX, offsetY++, "Food left:    %d", player->food);
  // terminal_printf(offsetX, offsetY++, "Steps:        %d", player->steps);
  // terminal_printf(offsetX, offsetY++, "Health:       %d", player->health);

  int score = player->cash * player->food - player->steps;
  if (score < 0) score = 0;

  int pos = 0;
  for (const auto& score1 : scores) {
    if (score1.value == score && player->name == score1.key) break;
    pos++;
  }

  offsetY++;
  // terminal_printf(offsetX, position.getY() + offsetY++, "Your score (%d): %d", pos + 1, score);

  offsetY += 5;

  // drawHeader({position.getX(), offsetY}, size, "TABLE SCORE");

  offsetY += 2;

  int i = 0;
  for (const auto& item : scores) {
    // terminal_printf(offsetX, position.getY() + offsetY++, "%d. %s: %d", i + 1, item.key.c_str(), item.value);

    i++;
    if (i == 10) break;
  } */
}
void EndGameScene::update(SceneManager* sceneManager) {
  // if (Input::getKey(TK_ENTER) || Input::getKey(TK_SPACE) || Input::getKey(TK_ESCAPE)) {
    // terminal_clear();
    // terminal_close();
    // sceneManager->switchScene("Menu");
  // }
}
EndGameScene::EndGameScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
void EndGameScene::start(SceneManager* sceneManager) {
  player = sceneManager->getContext()->getObject<PlayerDTO>();

  // read();

  int value = player->cash * player->food - player->steps;
  scores.emplace_back(player->name, value);
  std::sort(scores.begin(), scores.end(), [](const Score& lhs, const Score& rhs) { return lhs > rhs; });

  // write();
}

void EndGameScene::write() {
  std::string path = "Resource/scores.txt";
  std::ofstream file(path);

  if (file.is_open()) {
    std::cout << "File scores opens for write" << std::endl;

    for (const auto& item : scores) {
      file << item.key << " " << item.value << std::endl;
    }
  } else {
    std::cout << "File path: " << path << " doesn't exits!" << std::endl;
  }
}

void EndGameScene::read() {
  std::string buffer;
  std::string path = "Resource/scores.txt";
  std::ifstream file(path);

  if (file.is_open()) {
    std::cout << "File scores opens for readNames" << std::endl;

    std::string key;
    int value;
    while (!file.eof()) {
      file >> key >> value;
      scores.emplace_back(key, value);
      file.ignore();
    }

    file.close();
  } else {
    std::cout << "File path: " << path << " doesn't exits!" << std::endl;
  }
}
bool Score::operator<(const Score& rhs) const {
  return value < rhs.value;
}
bool Score::operator>(const Score& rhs) const {
  return rhs < *this;
}
bool Score::operator<=(const Score& rhs) const {
  return !(rhs < *this);
}
bool Score::operator>=(const Score& rhs) const {
  return !(*this < rhs);
}
