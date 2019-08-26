#include <BearLibTerminal.h>
#include <game/Scenes/AbilityScene.h>
#include <game/Scenes/BackpackScene.h>
#include <game/Scenes/ChestScene.h>
#include <game/Scenes/EndGameScene.h>
#include <game/Scenes/GameScene.h>
#include <game/Scenes/InputNameScene.h>
#include <game/Scenes/MenuScene.h>
#include <game/Scenes/ShopScene.h>
#include <game/Scenes/SpecialScene.h>
#include <game/Utility/Input.h>
#include <roomcreator/CreatorScene.h>
#include <ctime>
#include "game/Scenes/SceneManager.h"

int main() {
  terminal_open();

  terminal_set("window: title='Roguelike by ATF'");
  terminal_set("window: size=150x45");
  // terminal_set("window: cellsize=32x32, _size=40x40");
  terminal_set("palette.Usual = 255, 40, 180, 90");
  terminal_set("palette.Rare = 255, 0, 191, 255");
  terminal_set("palette.Epic = 255, 124, 17, 136");
  terminal_set("palette.Legendary = 255, 243, 215, 75");
  terminal_set("palette.Mythical = 255, 178, 34, 34");
  terminal_set("palette.Sublime = 255, 255, 218, 185");

  terminal_set("input.filter = [keyboard+, mouse+]");
  terminal_set("input.mouse-cursor = false");

  // terminal_set("0x40: Resource/Sprites/player.png, _size=32x32, align=center");
  // terminal_set("0x23: Resource/Sprites/wall.png, _size=32x32, align=center");
  // terminal_set("0x2E: Resource/Sprites/dot.png, _size=32x32, align=center");
  // terminal_set("0x45: Resource/Sprites/Enemy.png, _size=32x32, align=center");

  terminal_refresh();

  Context context{};
  SceneManager sceneManager(&context);
  sceneManager.addScene("Menu", new MenuScene(&context, &sceneManager));
  sceneManager.addScene("Game", new GameScene(&context, &sceneManager));
  sceneManager.addScene("InputName", new InputNameScene(&context, &sceneManager));
  sceneManager.addScene("Special", new SpecialScene(&context, &sceneManager));
  sceneManager.addScene("Ability", new AbilityScene(&context, &sceneManager));
  sceneManager.addScene("Chest", new ChestScene(&context, &sceneManager));
  sceneManager.addScene("Shop", new ShopScene(&context, &sceneManager));
  sceneManager.addScene("Backpack", new BackpackScene(&context, &sceneManager));
  sceneManager.addScene("EndGame", new EndGameScene(&context, &sceneManager));

  sceneManager.addScene("Creator", new CreatorScene(&context, &sceneManager));

  sceneManager.switchScene("Menu");
  sceneManager.start();
  terminal_refresh();

  // const int FRAMES_PER_SECOND = 60;
  // const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

  // int64_t next_game_tick = GetTickCount();

  int sleep_time = 0;

  auto begin = clock();
  auto ticks = 0;
  while (true) {
    if (Input::hasInput()) {
      // Input::updateAxis();

      sceneManager.update();
      sceneManager.render();

      if (Input::isPressed(TK_CLOSE)) break;

      terminal_refresh();
      Input::read();
    }

    // next_game_tick += SKIP_TICKS;
    // sleep_time = next_game_tick - GetTickCount();

    if (sleep_time >= 0) terminal_delay(sleep_time);
    // else
    // std::cout << "DELAY! " << sleep_time << std::endl;

    if (clock() - begin > 1000) {
      // std::cout << "FPS: " << ticks << std::endl;
      begin = clock();
      ticks = 0;
    }

    ticks++;
  }

  // sceneManager.end();
  terminal_close();
}
