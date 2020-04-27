//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_GUN_H
#define FINALPROJECT_GUN_H

namespace shooter {
class Gun {
 private:
  int gun_row_;
  int gun_col_;

 public:
  int GetGunRow();
  int GetGunCol();
};
}
#endif  // FINALPROJECT_GUN_H
