//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_GAME_ENGINE_H
#define FINALPROJECT_GAME_ENGINE_H

#include <vector>

#include "bullet.h"
#include "enemy.h"

namespace shooter {
using namespace std;

class GameEngine {
 private:
  const float kEnemySeparatingDistance = 70;
  const int kEnemies = 10;
  std::vector<Enemy> all_enemies;
  std::vector<Bullet> bullets;
  vec2 top_left_pos;

 public:
  GameEngine();
  std::vector<Enemy> *GetAllEnemies();
  std::vector<Bullet> *GetAllBullets();
  void InitializeEnemies();
  void InitializeBullets(const Bullet& bullet);
};
}


#endif  // FINALPROJECT_GAME_ENGINE_H
