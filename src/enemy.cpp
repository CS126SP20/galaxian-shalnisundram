//
// Created by Shalni Sundram on 4/22/20.
//

#include <shooter/enemy.h>


namespace shooter {

Enemy::Enemy(vec2 position, const Color& color, bool alive) {
  enemy_position_ = position;
  enemy_color_ = color;
  is_alive_ = alive;
}

vec2 Enemy::GetEnemyPosition() {
  return enemy_position_;
}

void Enemy::SetEnemyPosition(const vec2& position) {
  enemy_position_ = position;
}

bool Enemy::CheckEnemyAlive() {
  return is_alive_;
}


void Enemy::KillEnemy() {
  is_alive_ = false;
}
}

