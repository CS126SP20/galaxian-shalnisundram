//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_GAME_ENGINE_H
#define FINALPROJECT_GAME_ENGINE_H

#include <vector>

#include "bullet.h"
#include "enemy.h"
#include "gun.h"

namespace shooter {
using namespace std;

class GameEngine {
 public:
  GameEngine();

  std::vector<Enemy> *GetAllEnemies();

  std::vector<Bullet> *GetAllBullets();

  void MoveRight(float speed, float freq, float amp);

  void MoveLeft();

  void Reset();

  shooter::Gun GetGun() const;

  shooter::Bullet GetBullet() const;

  shooter::Enemy GetEnemy() const;

  void InitializeEnemies();

  void InitializeBullets(Bullet bullet);

 private:
  std::vector<Enemy> all_enemies;
  std::vector<Bullet> bullets;
  vec2 top_left_pos;
};
}


#endif  // FINALPROJECT_GAME_ENGINE_H
