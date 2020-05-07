//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_ENEMY_H
#define FINALPROJECT_ENEMY_H

#include "cinder/app/App.h"

#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace shooter {

class Enemy {

 private:
  vec2 enemy_position_;
  Color enemy_color_;
  bool is_alive_;

 public:
  Enemy(vec2 position, const Color& enemy_color_, bool is_alive_);
  vec2 GetEnemyPosition();
  void SetEnemyPosition(const vec2& position);
  bool CheckEnemyAlive();
  void KillEnemy();

};
}





#endif  // FINALPROJECT_ENEMY_H
