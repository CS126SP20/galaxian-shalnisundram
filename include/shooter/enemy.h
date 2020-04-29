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

 public:
  Enemy(vec2 position, Color color);
  vec2 GetEnemyPosition();
  void SetEnemyPosition(vec2 position);
  Color GetEnemyColor();
};
}





#endif  // FINALPROJECT_ENEMY_H
