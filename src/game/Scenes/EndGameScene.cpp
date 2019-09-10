//
// Created by AsTeFu on 16.07.2019.
//

#include "game/Scenes/EndGameScene.h"
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/PlayerComponents/NameComponent.h>
#include <game/Components/PlayerComponents/StepsComponent.h>
#include <game/RoomManager/Room.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <utilities/Terminal.h>
#include <algorithm>
#include <fstream>
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/Input.h"

void EndGameScene::render() {
  Vector2 position(20, 5);
  Vector2 size(100, 20);

  Terminal::setLayer(0);
  Terminal::clearArea(position, size);
  Terminal::setLayer(1);
  Terminal::clearArea(position, size);
  Terminal::setLayer(2);
  Terminal::clearArea(position, size);

  Terminal::setLayer(5);
  Terminal::setColor(Color::Red);
  SceneRenderUtility::drawBorder(position, size);

  int x = position.getX() + 5;
  int y = position.getY() + 2;

  Terminal::setColor(Color::White);
  Terminal::printf(x, y++, "Rooms:        %d", Room::countRoom);
  y += 1;

  Terminal::printf(x, y++, "Name:         %s", player->getComponent<NameComponent>()->name.c_str());
  Terminal::printf(x, y++, "Cash:         %d", player->getComponent<WalletComponent>()->cash);
  Terminal::printf(x, y++, "Food left:    %d", player->getComponent<StarvationComponent>()->currentFood);
  Terminal::printf(x, y++, "Steps:        %d", player->getComponent<StepsComponent>()->currentSteps);
  Terminal::printf(x, y++, "Health:       %d", player->getComponent<HealthComponent>()->health);

  int score = player->getComponent<WalletComponent>()->cash + player->getComponent<StarvationComponent>()->currentFood -
              player->getComponent<StepsComponent>()->currentSteps;
  if (score < 0) score = 0;

  Terminal::printf(x, y++, "Score:        %d", score);
}
void EndGameScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::Enter) || Input::getKeyDown(KeyCode::Space) || Input::getKeyDown(KeyCode::Escape)) {
    Terminal::clear();
    Terminal::close();
  }
}
EndGameScene::EndGameScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
void EndGameScene::start(SceneManager* sceneManager) {
  player = sceneManager->getContext()->getObject<PlayerDTO>();

  // read();

  // int value = player->cash * player->food - player->steps;
  // scores.emplace_back(player->name, value);
  // std::sort(scores.begin(), scores.end(), [](const Score& lhs, const Score& rhs) { return lhs > rhs; });

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
    std::cout << "File scores opens for readDirection" << std::endl;

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
