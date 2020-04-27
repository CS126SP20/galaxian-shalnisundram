//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_GAME_ENGINE_H
#define FINALPROJECT_GAME_ENGINE_H

#include "gun.h"
#include "bullet.h"
#include "enemy.h"
#include <vector>

namespace shooter {

class GameEngine {
 public:
  GameEngine();

  std::vector<Enemy> GetAllEnemies();

  void MoveRight(float speed, float freq, float amp);

  void MoveLeft();

  void Reset();

  shooter::Gun GetGun() const;

  shooter::Bullet GetBullet() const;

  shooter::Enemy GetEnemy() const;


 private:
  std::vector<Enemy> all_enemies;
  vec2 top_left_pos;
};
}


#endif  // FINALPROJECT_GAME_ENGINE_H
