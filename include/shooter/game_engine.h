//
// Created by Shalni Sundram on 4/22/20.
//

#ifndef FINALPROJECT_GAME_ENGINE_H
#define FINALPROJECT_GAME_ENGINE_H

class GameEngine() {
 public:

  void Move();

  void Reset();

  Gun GetGun() const;

  Bullet GetBullet() const;

  Enemy GetEnemy() const;

 private:
  Gun gun_;
  Bullet bullet_;
  Enemy enemy_;
  
}

#endif  // FINALPROJECT_GAME_ENGINE_H
