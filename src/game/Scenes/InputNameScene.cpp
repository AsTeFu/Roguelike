//
// Created by AsTeFu on 11.08.2019.
//

#include "game/Scenes/InputNameScene.h"
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Config.h>
#include <game/Utility/DTO/NameDTO.h>
#include <game/Utility/Input.h>
#include <utilities/KeyCode.h>
#include <utilities/StringUtility.h>
#include <utilities/Terminal.h>

InputNameScene::InputNameScene(Context *const context, SceneManager *sceneManager) : Scene(context, sceneManager) {
  sizeLabel = {Config::getInstance().sizeTerminal.getX() - leftMargin * 4, 4};
  positonPica = {Config::getInstance().sizeTerminal.getX() - 30, Config::getInstance().sizeTerminal.getY() - 10};
  positionInput = {positionLabel.getX() + leftMargin / 2 + 17, positionLabel.getY() + topMargin + sizeLabel.getY()};
}
void InputNameScene::start(SceneManager *sceneManager) {
  Input::read();
  render();

  name = Terminal::readString(positionInput, rangeLen.maxValue);
  StringUtility::trim(&name);
  if (static_cast<int>(name.size()) >= rangeLen.minValue) {
    Terminal::clear();
    sceneManager->getContext()->addObject<NameDTO>(name);
    sceneManager->switchScene(specialScene);
  }
}

void InputNameScene::update(SceneManager *sceneManager) {}
void InputNameScene::render() {
  SceneRenderUtility::drawHeader(positionLabel, sizeLabel, "Познокомимся?");

  int x = positionLabel.getX() + leftMargin / 2;
  int y = positionLabel.getY() + topMargin + sizeLabel.getY();

  Terminal::print(x, y++, "Input your name: ");
  Terminal::print(x, y, "Больше " + std::to_string(rangeLen.minValue) + " букв!");
  drawPica();
}
void InputNameScene::drawPica() const {
  Terminal::print(positonPica,
                  "                 {\\__/} \n"
                  "введи свое имя   (●_● ) \n"
                  "без пробелов pls (< < )");
}
