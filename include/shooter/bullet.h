//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H


#include "cinder/app/App.h"
#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace shooter {

class Bullet {

 private:
  vec2 bullet_position_;

 public:
  Bullet(const vec2& bullet_position_);
  vec2 GetBulletPosition();
  void SetBulletPosition(vec2 position);
};
}

#endif  // FINALPROJECT_BULLET_H
