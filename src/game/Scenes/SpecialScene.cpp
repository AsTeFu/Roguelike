//
// Created by AsTeFu on 26.07.2019.
//

#include "game/Scenes/SpecialScene.h"
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/DTO/SpecialDTO.h>
#include <utilities/FileUtility.h>
#include <utilities/MathUtility.h>
#include <utilities/StringUtility.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "game/Scenes/GameScene.h"
#include "game/Utility/Config.h"
#include "game/Utility/Input.h"

SpecialScene::SpecialScene(Context* context, SceneManager* sceneManager)
    : Scene(context, sceneManager),
      _description(FileUtility::readDescription("Resource/Direction/Description.txt")),
      _currentPos(0),
      _special(Config::getInstance().pointSpecialRange, Config::getInstance().maxPointsSpecial) {
  for (const auto& stat : Config::getInstance().statsSpecial) _special.addPoints(stat, 4);

  positionLabel = {leftMargin * 2, topMargin};
  sizeLabel = {Config::getInstance().sizeTerminal.getX() - leftMargin * 4, 4};

  positionStats = {leftMargin * 3, sizeLabel.getY() + topMargin * 2};
  sizeStats = {40, 21};

  positionDescription = {positionStats.getX() + sizeStats.getX() + leftMargin, positionStats.getY()};
  sizeDescription = {Config::getInstance().sizeTerminal.getX() - sizeStats.getX() - leftMargin * 7, 21};
}
void SpecialScene::increaseCurrentStat() {
  _special.addPoint(Config::getInstance().statsSpecial[_currentPos]);
}
void SpecialScene::decreaseCurrentStat() {
  _special.removePoint(Config::getInstance().statsSpecial[_currentPos]);
}
void SpecialScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::UpArrow)) upward();
  if (Input::getKeyDown(KeyCode::DownArrow)) downward();

  if (Input::getKeyDown(KeyCode::LeftArrow)) decreaseCurrentStat();
  if (Input::getKeyDown(KeyCode::RightArrow)) increaseCurrentStat();

  if (Input::getKeyDown(KeyCode::Enter) && _special.countPoints() == 0) {
    _context->addObject<SpecialDTO>(_special);
    sceneManager->switchScene(gameScene);
  }
}

void SpecialScene::downward() {
  _currentPos = MathUtility::clamp(_currentPos + 1, 0, _special.size() - 1);
}
void SpecialScene::upward() {
  _currentPos = MathUtility::clamp(_currentPos - 1, 0, _special.size() - 1);
}

void SpecialScene::start(SceneManager* sceneManager) {
  render();
}
void SpecialScene::end(SceneManager* sceneManager) {}
void SpecialScene::render() {
  Terminal::clear();

  SceneRenderUtility::drawHeader(positionLabel, sizeLabel, "S.P.E.C.I.A.L.");

  int x = positionStats.getX();
  int y = positionStats.getY();

  SceneRenderUtility::drawBorder(positionStats, sizeStats);
  x += leftMargin + 1;
  y += topMargin / 2 + 1;

  y = renderStat(x, y);
  y = renderDescriptions(x, y);
}
int SpecialScene::renderStat(int x, int y) const {
  Terminal::printf(x, y++, "POINTS REMAINING: %d", _special.countPoints());
  y += 2;

  Terminal::print(x - _cursor.size() - 1, y + _currentPos * 2, _cursor);
  for (const auto& stat : Config::getInstance().statsSpecial) y = drawStat(x, y, stat);

  y += 5;
  SceneRenderUtility::drawHeader(leftMargin * 3, y, Config::getInstance().sizeTerminal.getX() - leftMargin * 6, 4,
                                 "Распредели все очки и нажми Enter");
  return y;
}
int SpecialScene::drawStat(int x, int y, const string& stat) const {
  switchColor(stat);

  Terminal::print(x, y, StringUtility::toUpper(stat));
  // TODO(AsTeFu): 19 is magic number
  // Как вариант заменить его на поиск самого длинного названия и делать отступ от него. Тут я его сам посчитал
  Terminal::printf(x + 19, y, "%d", _special.getValue(stat));

  drawInputButtons(x, y, stat);
  y += 2;
  return y;
}
void SpecialScene::drawInputButtons(int x, int y, const string& stat) const {
  Terminal::setColor(Color::White);
  int offsetX = 0;
  if (_special.getValue(stat) > Config::getInstance().pointSpecialRange.minValue) {
    Terminal::print(x + 23, y, "[[-]]");
    offsetX += 4;
  }
  if (_special.getValue(stat) < Config::getInstance().maxPointsSpecial && _special.countPoints() > 0)
    Terminal::print(x + 23 + offsetX, y, "[[+]]");
}
void SpecialScene::switchColor(const string& stat) const {
  if (_special.getValue(stat) >= 7)
    Terminal::setColor(Color::Green);
  else if (_special.getValue(stat) >= 4)
    Terminal::setColor(Color::Yellow);
  else
    Terminal::setColor(Color::Red);
}
int SpecialScene::renderDescriptions(int x, int y) const {
  x = positionDescription.getX() + leftMargin;
  y = positionDescription.getY() + topMargin;

  SceneRenderUtility::drawBorder(positionDescription, sizeDescription);
  Terminal::print(x, y, "DESCRIPTION:");
  y += 2;
  drawDescription(x, y);
  return y;
}
void SpecialScene::drawDescription(int x, int y) const {
  std::vector<string> currentDescription = StringUtility::split(_description[_currentPos], ' ');
  int currentlen = 0;
  int currentY = 0;
  for (const auto& word : currentDescription) {
    Terminal::print(x + currentlen, y + currentY, word);
    currentlen += static_cast<int>(word.size()) / 2 + 1;
    if (currentlen > lineLen) {
      currentlen = 0;
      currentY++;
    }
  }
}
