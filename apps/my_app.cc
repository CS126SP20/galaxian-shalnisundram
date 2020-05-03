// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "shooter/enemy.h"
#include "shooter/game_engine.h"
#include <algorithm>
#include <iostream>
#include "shooter/bullet.h"
#include "my_app.h"


#include "pretzel/PretzelGui.h"

namespace myapp {

using namespace ci;
using namespace ci::app;
using namespace std;

MyApp::MyApp() {}

void MyApp::setup() {
  Rand::randomize();

  time = 0;
  easy_speed_ = 0;
  med_speed_ = 0;
  hard_speed_ = 0;
  easy_radius_ = 25;
  med_radius_ = 10;
  hard_radius_ = 5;
  game_radius_ = 0;
  mOpacity = 0.75;
  gun_x_pos_ = getWindowWidth() * .5 + 30;
  gun_x_pos_two_ = gun_x_pos_ + 50;
  gun_height_ = getWindowHeight() - 70;
  mPosition = getWindowCenter();
  mCol = Color::white();

  mStringList = {"one", "two", "three"};

  gui = pretzel::PretzelGui::create("Straight Shooting");

  gui->addLabel("Set Difficulty");
  gui->addToggle("Easy", &bMakeEasy);
  gui->addToggle("Medium", &bMakeMed);
  gui->addToggle("Hard", &bMakeHard);

  game_engine_.InitializeEnemies();
}

void MyApp::keyDown(KeyEvent event) {

  // Allows right/left arrow keys to move the gun
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      MoveRight();
      break;
    }
    case KeyEvent::KEY_LEFT: {
      MoveLeft();
    }
  }

  // Shoots bullet by hitting space bar
  if (event.getCode() == KeyEvent::KEY_SPACE) {
    shooter::Bullet new_bullet({(gun_x_pos_ +
    (gun_x_pos_two_ - gun_x_pos_) / 2), gun_height_});  // Bullet launch position set to center of gun's top edge
    PlayLaserAudio();
    game_engine_.InitializeBullets(new_bullet);
  }
}

void MyApp::mouseDown(MouseEvent event) {}

void MyApp::onButtonPress() {
  mCol =
      ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
}

void MyApp::update() {
  time += .1;
  easy_speed_ += .3;
  med_speed_ += .7;
  hard_speed_ += 1;
  enemy_position.x += 2;
  mPosition.x += 2;
  mPosition.x = mPosition.x + sin(time) * 7;

  // Moves enemy in a sin motion
  vector<shooter::Enemy> *these_enemies = game_engine_.GetAllEnemies();
  for (auto & enemy : *these_enemies) {
    vec2 current_position = enemy.GetEnemyPosition();
    current_position.x += sin(time) * 7;
    enemy.SetEnemyPosition(current_position);
  }
  MoveBullet();
  EraseHitEnemy();
}

void MyApp::draw() {
  gl::clear(Color(84. / 255., 166. / 255., 1));
  gl::color(mCol);
  mCol.a = mOpacity;
  DrawGun();
  DrawEnemies();
  DrawBullet();
  gui->draw(); // Draws toggles on the side of the window
}

void MyApp::DrawEnemies() {
  red_color = ColorA(1.0, 1.0, 0.0, mOpacity);
  gl::color(red_color);
  vector<shooter::Enemy> *enemies = game_engine_.GetAllEnemies();

  // Iterates through all enemies and draw circles to represent them
  for (auto & enemy : *enemies) {
    enemy_position = enemy.GetEnemyPosition();

    // Set radius and draw circles based on the difficulty level selected
    if (enemy.CheckEnemyAlive()) { // Only draw enemies that haven't been hit
      if (bMakeEasy) {
        game_radius_ = easy_radius_;
        gl::drawSolidCircle(enemy_position, game_radius_);
      } else if (bMakeMed) {
        game_radius_ = med_radius_;
        gl::drawSolidCircle(enemy_position, game_radius_);
      } else if (bMakeHard) {
        game_radius_ = hard_radius_;
        gl::drawSolidCircle(enemy_position, game_radius_);
      } else {
        game_radius_ = easy_radius_;
        gl::drawSolidCircle(enemy_position, game_radius_);
      }
    }
  }
}

void MyApp::DrawGun() {
  gl::drawSolidRect(Rectf(gun_x_pos_, getWindowHeight() - 70, gun_x_pos_two_,
                          getWindowHeight()));
}

void MyApp::DrawBullet() {
  mCol = ColorA(1.0, 0.0, 0.0, mOpacity);
  gl::color(mCol);
  std::vector<shooter::Bullet> *bullets = game_engine_.GetAllBullets();

  // Draws bullet for every entry in the bullets vector
  for (auto & bullet : *bullets) {
    gl::drawSolidCircle(bullet.GetBulletPosition(), 5);
  }
}

void MyApp::MoveRight() {
  gun_x_pos_ += 10;
  gun_x_pos_two_ += 10;
}

void MyApp::MoveLeft() {
  gun_x_pos_ -= 10;
  gun_x_pos_two_ -= 10;
}

void MyApp::MoveBullet() {
  std::vector<shooter::Bullet> *bullets = game_engine_.GetAllBullets();

  // Iterate through all bullets and set its position to the gun's center
  for (auto & bullet : *bullets) {
    vec2 pos = bullet.GetBulletPosition();
    pos.y -= 5;
    bullet.SetBulletPosition(pos);
  }
}

void MyApp::EraseHitEnemy() {
  std::vector<shooter::Bullet> *bullets = game_engine_.GetAllBullets();
  std::vector<shooter::Enemy> *enemies = game_engine_.GetAllEnemies();

  // Iterate through every enemy for every bullet
  // Check if distance between enemy and bullet is small than enemy radius
  for (auto & bullet : *bullets) {
    for (auto & enemy : *enemies) {
      vec2 bullet_pos = bullet.GetBulletPosition();
      vec2 enemy_pos = enemy.GetEnemyPosition();
      float distance_x = (bullet_pos.x - enemy_pos.x);
      float distance_y = (bullet_pos.y - enemy_pos.y);
      float distance = std::sqrtf((distance_x * distance_x) + (distance_y * distance_y));

      if (distance <= game_radius_) { // bullet has intersected the enemy
        if (enemy.CheckEnemyAlive()) {
          PlayEnemyPopAudio();
        }
        enemy.KillEnemy();
      }
    }
  }
}

void MyApp::PlayLaserAudio() {
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset( "laser_audio.wav"));
  laser_sound_ = cinder::audio::Voice::create( sourceFile );

  // Start playing background music
  laser_sound_->start();
}

void MyApp::PlayEnemyPopAudio() {
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset( "enemy_pop.wav"));
  enemy_pop_ = cinder::audio::Voice::create( sourceFile );

  // Start playing background music
  enemy_pop_->start();
}
} // namespace myapp

CINDER_APP(myapp::MyApp, RendererGl, [](App::Settings* settings){
  settings->prepareWindow(Window::Format().size(1024, 768).title("PrezelGui :: BasicSample"));
  settings->setFrameRate(60.0f);
//	settings->setHighDensityDisplayEnabled();
})
