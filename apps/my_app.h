// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "pretzel/PretzelGui.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "shooter/enemy.h"
#include "shooter/game_engine.h"
#include <algorithm>
#include <iostream>
#include <cinder/audio/audio.h>

namespace myapp {

enum class GameState {
  kPreGame,
  kActive,
  kGameWon,
  kGameLost,
};

class MyApp : public cinder::app::App {

 private:
  const int kGunHeight = getWindowHeight() - 70;
  const int kTotalTime = 45;
  const int kWindowHeightPortion = 70;
  const int kGunWidth = 50;
  const double kGunInitialXPos = getWindowWidth() * .5 + 30;
  const float kInitialOpacity = 0.75;
  const float kTimeChange = 0.1;
  const float kEasyRadius = 25;
  const float kMedRadius = 10;
  const float kHardRadius = 5;
  const float kBulletRadius = 5;
  const float kTimerSize = 30;
  const float kBulletPositionChange = 5;
  const float kBigTextSize = 75;
  const float kEnemyCurveAmplitude = 7.0;
  const float kGunPositionChange = 10.0;
  const float kEnemyPositionChange = 2.0;
  const float kEasyPositionChange = 0.3;
  const float kMedPositionChange = 0.7;
  const float kHardPositionChange = 1;
  const float kDefaultGameRadius = 10;
  const vec2 kClockBoxLocation = {50, 50};
  const vec2 kClockBoxSize = {50, 50};
  const vec2 kBigTextBoxSize = {350, 250};
  const vec2 kTextBoxLocation = getWindowCenter();

 public:
  MyApp();
  void setup() override;
  void keyDown(KeyEvent event) override;
  void onButtonPress();
  void update() override;
  void draw() override;
  void DrawEnemies();
  void DrawGun();
  void DrawBullet();
  void DrawTimeRemaining();
  void DrawGameTitle();
  void DrawGameOver();
  void PrintTextBox(vec2 &location, float text_size_, const vec2& box_size_,
      const string& text);
  void MoveEnemy();
  void MoveGunRight();
  void MoveGunLeft();
  void MoveBullet();
  void EraseHitEnemy();
  bool CheckGameWinner();
  bool CheckGameLoser();
  void PlayLaserAudio();
  void PlayEnemyPopAudio();
  void PlayGameMusic();

  pretzel::PretzelGuiRef pregame_gui_;
  shooter::GameEngine game_engine_;
  int defeated_enemy_count_;
  int time_remaining_;
  float easy_radius_;
  float med_radius_;
  float hard_radius_;
  float game_radius_;
  float mOpacity;
  float time;
  float easy_speed_;
  float med_speed_;
  float hard_speed_;
  double gun_x_pos_two_;
  double gun_x_pos_;
  double gun_height_;
  bool bMakeEasy;
  bool bMakeMed;
  bool bMakeHard;
  vec2 enemy_position;
  GameState game_state_;
  ci::ColorA mCol;
  ci::ColorA red_color;
  cinder::audio::VoiceRef laser_sound_;
  cinder::audio::VoiceRef enemy_pop_;
  cinder::audio::VoiceRef game_music_;
  cinder::Timer time_elapsed_;
};
}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
