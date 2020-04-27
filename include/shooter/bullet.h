//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H

namespace shooter {

class Bullet {
 public:
  Bullet();

 private:
  int bullet_row_;
  int bullet_col_;

 public:
  int GetBulletRow();
  int GetBulletCol();

};
}

#endif  // FINALPROJECT_BULLET_H
