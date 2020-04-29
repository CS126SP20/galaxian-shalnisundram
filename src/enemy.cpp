//
// Created by Shalni Sundram on 4/22/20.
//

#include <shooter/enemy.h>


namespace shooter {

Enemy::Enemy(vec2 position, Color color) {
  enemy_position_ = position;
  enemy_color_ = color;
}

vec2 Enemy::GetEnemyPosition() {
  return enemy_position_;
}

void Enemy::SetEnemyPosition(vec2 position) {
  enemy_position_ = position;
}

Color Enemy::GetEnemyColor() {
  return enemy_color_;
}



}

