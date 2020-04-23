//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_GUN_H
#define FINALPROJECT_GUN_H

namespace shooter {
class Gun {
 public:
  Gun(const Location&);

  Location GetLocation();

 private:
  Location location_;
};
}
#endif  // FINALPROJECT_GUN_H
