//
// Created by AsTeFu on 21.08.2019.
//

#include <BearLibTerminal.h>
#include <editor/Components/BrushComponent.h>
#include <editor/Components/BrushesComponent.h>
#include <editor/Components/ColorComponent.h>
#include <editor/Components/ColorsComponent.h>
#include <editor/Components/DirectoryComponent.h>
#include <editor/Components/FileNameComponent.h>
#include <editor/Components/StructureComponent.h>
#include <editor/CreatorScene.h>
#include <editor/CreatorUtility.h>
#include <editor/Systems/BrushSystem.h>
#include <editor/Systems/ColorSystem.h>
#include <editor/Systems/FileSystem.h>
#include <editor/Systems/StructureSystem.h>
#include <game/Utility/Config.h>
#include <game/Utility/Input.h>
#include <game/Utility/Utility.h>
#include <utilities/FileUtility.h>
#include <map>
#include <string>
#include <vector>

void CreatorScene::update(SceneManager* sceneManager) {
  _engine.update();

  if (Input::getKey(KeyCode::Escape)) {
    terminal_clear();
    sceneManager->switchScene("Menu");
  }
}
void CreatorScene::start(SceneManager* sceneManager) {
  _engine = Engine(sceneManager);
  terminal_set("input.mouse-cursor = true");

  auto roomStruct = CreatorUtility::createStructure(&_engine);
  auto directory = readDirectory(roomsPath)->getComponent<DirectoryComponent>();

  if (directory->directory.empty()) CreatorUtility::addEmptyRoom(roomsPath, roomStruct, directory);
  FileUtility::readRoom(roomsPath + directory->directory[0], roomStruct->getComponent<StructureComponent>());

  setBrushes();
  setColors();

  auto brush = _engine.getEntityManager()->createEntity("brush");
  auto startBrush = _engine.getEntityManager()->getByTag("brushes")[0]->getComponent<BrushesComponent>();
  auto startColor = _engine.getEntityManager()->getByTag("colors")[0]->getComponent<ColorsComponent>();

  brush->addComponent<BrushComponent>(startBrush->brushes[0]);
  brush->addComponent<ColorComponent>(startColor->colors[0]);

  activateSystem();
}

void CreatorScene::activateSystem() {
  _engine.getSystemManager()->addSystem<FileSystem>(filePositions, roomsPath);
  _engine.getSystemManager()->addSystem<StructureSystem>(structurePositions);
  _engine.getSystemManager()->addSystem<BrushSystem>(brushPositions);
  _engine.getSystemManager()->addSystem<ColorSystem>(colorPositions);
}

Entity* CreatorScene::readDirectory(const std::string& path) {
  auto directory = _engine.getEntityManager()->createEntity();
  directory->addComponent<DirectoryComponent>();
  auto filenames = Utility::readNames(path);
  for (const auto& name : filenames) {
    directory->getComponent<DirectoryComponent>()->directory.emplace_back(name);
  }
  return directory;
}

void CreatorScene::render() {}

CreatorScene::CreatorScene(Context* const context, SceneManager* sceneManager)
    : Scene(context, sceneManager), _engine(sceneManager) {}

void CreatorScene::setBrushes() {
  std::map<char, std::string> symbols = FileUtility::readBrushes(brushesPath);

  auto brushes = _engine.getEntityManager()->createEntity("brushes");
  brushes->addComponent<BrushesComponent>();

  for (const auto& symbol : symbols) {
    auto brush = _engine.getEntityManager()->createEntity();
    brush->addComponent<BrushComponent>(symbol.second, symbol.first);
    brushes->getComponent<BrushesComponent>()->brushes.emplace_back(brush->getComponent<BrushComponent>());
  }
}
void CreatorScene::setColors() {
  std::map<std::string, Color> readColors = FileUtility::readColors(colorsPath);

  auto colors = _engine.getEntityManager()->createEntity("colors");
  colors->addComponent<ColorsComponent>();

  for (const auto& clr : readColors) {
    auto color = _engine.getEntityManager()->createEntity();
    color->addComponent<ColorComponent>(clr.first.c_str(), clr.second);
    colors->getComponent<ColorsComponent>()->colors.push_back(color->getComponent<ColorComponent>());
  }
}
