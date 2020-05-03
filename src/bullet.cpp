//
// Created by Shalni Sundram on 4/22/20.
//

#include <shooter/bullet.h>

namespace shooter {

Bullet::Bullet(const vec2& position) {
  bullet_position_ = position;
}

vec2 Bullet::GetBulletPosition() {
  return bullet_position_;
}

void Bullet::SetBulletPosition(vec2 position) {
  bullet_position_ = position;
}
}
