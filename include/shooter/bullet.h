//
// Created by Shalni Sundram on 4/22/20.
//

#include "cinder/app/App.h"

#include "pretzel/PretzelGui.h"

#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H

using namespace ci;
using namespace ci::app;
using namespace std;

namespace shooter {

class Bullet {
 public:
  Bullet();

 private:
  vec2 bullet_position_;

 public:
  void SetEnemyPosition();
  vec2 GetBulletPosition();
};
}

#endif  // FINALPROJECT_BULLET_H
