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
  : top_left_pos{getWindowPos()}
{}

void GameEngine::InitializeEnemies() {
  const Color red_color = Color::hex(0xFF0000);
  for (int i = 0; i < 10; i++) {
    if (i >= 1) {
      top_left_pos.x = all_enemies[i - 1].GetEnemyPosition().x + 80;
    }
    Enemy new_enemy(top_left_pos, red_color, true);
    all_enemies.push_back(new_enemy);
  }
}

void GameEngine::InitializeBullets(Bullet bullet) {
  bullets.push_back(bullet);
}

std::vector<Enemy>* GameEngine::GetAllEnemies() {
  return &all_enemies;
}

std::vector<Bullet>* GameEngine::GetAllBullets() {
  return &bullets;
}

}
