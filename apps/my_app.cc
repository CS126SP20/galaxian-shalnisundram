// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "cinder/app/RendererGl.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "shooter/enemy.h"
#include <algorithm>
#include <iostream>
#include "shooter/bullet.h"
#include "pretzel/PretzelGui.h"

const char kTextFont[] = "Arial Bold";

using cinder::TextBox;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace myapp {

using std::chrono::seconds;
using std::chrono::system_clock;

MyApp::MyApp() {
  time = 0;
  game_radius_ = 0;
  defeated_enemy_count_ = 0;
  easy_speed_ = 0;
  med_speed_ = 0;
  hard_speed_ = 0;
  time_remaining_ = kTotalTime;
  easy_radius_ = kEasyRadius;
  med_radius_ = kMedRadius;
  hard_radius_ = kHardRadius;
  mOpacity = kInitialOpacity;
  gun_x_pos_ = kGunInitialXPos;
  gun_x_pos_two_ = gun_x_pos_ + kGunWidth;
  gun_height_ = getWindowHeight() - kWindowHeightPortion;
  mCol = Color::white();
  game_state_ = {GameState::kPreGame};
  bMakeEasy = false;
  bMakeMed = false;
  bMakeHard = false;
}

void MyApp::setup() {
  Rand::randomize();

  // Create gui
  pregame_gui_ = pretzel::PretzelGui::create("Straight Shooting");
  pregame_gui_->addButton("Launch", &MyApp::onButtonPress,
      this);
  pregame_gui_->addLabel("Set Difficulty");
  pregame_gui_->addToggle("Easy", &bMakeEasy);
  pregame_gui_->addToggle("Medium", &bMakeMed);
  pregame_gui_->addToggle("Hard", &bMakeHard);
  pregame_gui_ -> draw();
  game_engine_.InitializeEnemies();
}

void MyApp::keyDown(KeyEvent event) {

  // Allows right/left arrow keys to move the gun
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      MoveGunRight();
      break;
    }
    case KeyEvent::KEY_LEFT: {
      MoveGunLeft();
    }
  }

  // Shoots bullet by hitting space bar
  if (event.getCode() == KeyEvent::KEY_SPACE) {

    // Bullet launch position set to center of gun's top edge
    shooter::Bullet new_bullet({(gun_x_pos_ +
    (gun_x_pos_two_ - gun_x_pos_) / 2), gun_height_});
    PlayLaserAudio();
    game_engine_.InitializeBullets(new_bullet);
  }
}

void MyApp::onButtonPress() {
  game_state_ = GameState::kActive;
  time_elapsed_.start();
  PlayGameMusic();
  mCol =
      ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(),
          mOpacity);
}

void MyApp::update() {
  time += kTimeChange;
  easy_speed_ += kEasyPositionChange;
  med_speed_ += kMedPositionChange;
  hard_speed_ += kHardPositionChange;
  enemy_position.x += kEnemyPositionChange;
  //enemy_position.y += kEnemyPositionChange;
  // Check if the game is over
  if (CheckGameWinner() || CheckGameLoser()) {
    DrawGameOver();
  }

  // Timer countdown
  time_remaining_ = kTotalTime - ((int) time_elapsed_.getSeconds());
  MoveEnemy();
  MoveBullet();
  EraseHitEnemy();
}

void MyApp::draw() {

  // Creates settings for pregame
  if (game_state_ == GameState::kPreGame) {
    gl::clear(Color(0,0,1));
    DrawGameTitle();
    pregame_gui_ -> draw();
  }
  // Creates settings/draws for an active game
  if (game_state_ == GameState::kActive) {
    gl::clear(Color(84. / 255., 50. / 255., 1));
    gl::color(mCol);
    mCol.a = mOpacity;
    DrawTimeRemaining();
    DrawGun();
    DrawEnemies();
    DrawBullet();
  }
}

void MyApp::DrawEnemies() {
  red_color = ColorA(0, 0, 0, mOpacity);
  gl::color(red_color);
  vector<shooter::Enemy> *enemies = game_engine_.GetAllEnemies();

  // Iterates through all enemies and draw circles to represent them
  for (auto & enemy : *enemies) {
    enemy_position = enemy.GetEnemyPosition();
    // Sets radius and draw circles based on the difficulty level selected
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
        gl::drawSolidCircle(enemy_position, kDefaultGameRadius);
      }
    }
  }
}

void MyApp::DrawGun() {
  ci::ColorA gunColor = ColorA(0, 1, 0);
  gl::color(gunColor);
  gl::drawSolidRect(Rectf(gun_x_pos_, kGunHeight, gun_x_pos_two_,
                          getWindowHeight()));
}

void MyApp::DrawBullet() {
  mCol = ColorA(1.0, 0.0, 0.0, mOpacity);
  gl::color(mCol);
  std::vector<shooter::Bullet> *bullets = game_engine_.GetAllBullets();

  // Draws bullet for every entry in the bullets vector
  for (auto & bullet : *bullets) {
    gl::drawSolidCircle(bullet.GetBulletPosition(), kBulletRadius);
  }
}

void MyApp::DrawTimeRemaining() {
  PrintTextBox(const_cast<vec2 &>(kClockBoxLocation), kTimerSize,
      kClockBoxSize,to_string(time_remaining_));
}

void MyApp::DrawGameTitle() {
  PrintTextBox(const_cast<vec2 &>(kTextBoxLocation), kBigTextSize,
      kBigTextBoxSize, "Straight Shooting");
}

void MyApp::DrawGameOver() {
  vec2 result_loc = getWindowCenter();
  string result_text;
  if (game_state_ == GameState::kGameWon) {
    result_text = "You Won!";
  } else if (game_state_ == GameState::kGameLost){
    result_text = "You Lost";
  }
  PrintTextBox(const_cast<vec2 &>(kTextBoxLocation), kBigTextSize,
      kBigTextBoxSize, result_text);
}


// Some code to create text box from CS126 snake PrintText() function
void MyApp::PrintTextBox(vec2 &location, float text_size_,
    const vec2& box_size_, const string& text) {
  auto text_box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kTextFont, text_size_))
      .size(box_size_)
      .color(mCol)
      .text(text);

  const auto box_size = text_box.getSize();
  const cinder::vec2 box_location = { (location.x - (box_size.x / 2)),
                                      (location.y - box_size.y / 2)};
  const auto surface = text_box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, box_location);
}

void MyApp::MoveEnemy() {

  // Moves enemy in a sin motion
  vector<shooter::Enemy> *these_enemies = game_engine_.GetAllEnemies();
  for (auto & enemy : *these_enemies) {
    vec2 current_position = enemy.GetEnemyPosition();
    current_position.x += sin(time) * kEnemyCurveAmplitude;
    enemy.SetEnemyPosition(current_position);
  }
}

void MyApp::MoveGunRight() {
  gun_x_pos_ += kGunPositionChange;
  gun_x_pos_two_ += kGunPositionChange;
}

void MyApp::MoveGunLeft() {
  gun_x_pos_ -= kGunPositionChange;
  gun_x_pos_two_ -= kGunPositionChange;
}

void MyApp::MoveBullet() {
  std::vector<shooter::Bullet> *bullets = game_engine_.GetAllBullets();

  // Iterates through all bullets and set its position to the gun's center
  for (auto & bullet : *bullets) {
    vec2 pos = bullet.GetBulletPosition();
    pos.y -= kBulletPositionChange;
    bullet.SetBulletPosition(pos);
  }
}

void MyApp::EraseHitEnemy() {
  std::vector<shooter::Bullet> *bullets = game_engine_.GetAllBullets();
  std::vector<shooter::Enemy> *enemies = game_engine_.GetAllEnemies();

  // Iterates through every enemy for every bullet
  // Checks if distance between enemy and bullet is small than enemy radius
  for (auto & bullet : *bullets) {
    for (auto & enemy : *enemies) {
      vec2 bullet_pos = bullet.GetBulletPosition();
      vec2 enemy_pos = enemy.GetEnemyPosition();
      float distance_x = (bullet_pos.x - enemy_pos.x);
      float distance_y = (bullet_pos.y - enemy_pos.y);
      float distance = std::sqrtf((distance_x * distance_x) +
          (distance_y * distance_y));

      if (distance <= game_radius_) { // Bullet has intersected the enemy
        if (enemy.CheckEnemyAlive()) {
          defeated_enemy_count_++;
          PlayEnemyPopAudio();
        }
        enemy.KillEnemy();
      }
    }
  }
}

bool MyApp::CheckGameWinner() {
  if (time_remaining_ > 0 &&
      defeated_enemy_count_ == game_engine_.GetAllEnemies()->size()) {
    game_state_ = GameState::kGameWon;
    return true;
  }
  return false;
}

bool MyApp::CheckGameLoser() {
  if (time_remaining_ == 0 && defeated_enemy_count_
                              != game_engine_.GetAllEnemies()->size()) {
    time_elapsed_.stop();
    game_state_ = GameState::kGameLost;
    return true;
  }
  return false;
}

// Code for PlayLaserAudio(), PlayEnemyPopAudio(), and PlayGameMusic() from
// https://libcinder.org/docs/guides/audio/index.html
void MyApp::PlayLaserAudio() {
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset( "laser_audio.wav"));
  laser_sound_ = cinder::audio::Voice::create( sourceFile );

  // Start playing laser sound
  laser_sound_->start();
}

void MyApp::PlayEnemyPopAudio() {
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset( "enemy_pop.wav"));
  enemy_pop_ = cinder::audio::Voice::create( sourceFile );

  // Start playing pop sound
  enemy_pop_->start();
}

void MyApp::PlayGameMusic() {
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset( "80s_synth_pop.mp3"));
  game_music_ = cinder::audio::Voice::create( sourceFile );

  // Start playing background music
  game_music_->start();
}
} // namespace myapp

CINDER_APP(myapp::MyApp, RendererGl, [](App::Settings* settings){
  settings->prepareWindow(Window::Format().size(1024, 768).
  title("PrezelGui :: MyApp"));
  settings->setFrameRate(60.0f);
//	settings->setHighDensityDisplayEnabled();
})
