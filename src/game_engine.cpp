//
// Created by Shalni Sundram on 4/22/20.
//

#include "shooter/game_engine.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"

#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace shooter {

GameEngine::GameEngine()
  : top_left_pos{getWindowPos()},
    all_enemies{}
{}

std::vector<Enemy> GameEngine::GetAllEnemies() {
  const Color red_color = Color::hex(0xFF0000);
  Enemy first_enemy(top_left_pos, red_color);
  all_enemies.push_back(first_enemy);
  for (int i = 0; i < 10; i++) {
    top_left_pos.x = i;
    Enemy new_enemy(top_left_pos, red_color);
    all_enemies.push_back(new_enemy);
  }
  return all_enemies;
}

}
