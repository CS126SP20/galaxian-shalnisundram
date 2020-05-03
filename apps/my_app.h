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

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  static void prepareSettings(Settings *settings);
  void setup();
  void mouseDown(MouseEvent event);
  void update();
  void draw();
  void keyDown(KeyEvent event);
  void DrawGun();
  void DrawBullet();
  void DrawEnemies();
  void MoveGun();
  void MoveBullet();
  void MoveRight();
  void MoveLeft();
  void UpdateEnemies();
  void EraseHitEnemy();

 public:
  pretzel::PretzelGuiRef gui;

  shooter::GameEngine game_engine_;
  float easy_radius_;
  float med_radius_;
  float hard_radius_;
  float game_radius_;
  float mOpacity;
  float time;
  float easy_speed_;
  float med_speed_;
  float hard_speed_;
  float gun_x_pos_;
  float gun_x_pos_two_;
  float gun_height_;

  bool bMakeEasy;
  bool bMakeMed;
  bool bMakeHard;

  vec2 mPosition;
  vec2 enemy_position;
  vec2 bullet_position_;

  string mFps;

  ci::ColorA mCol;
  ci::ColorA red_color;
  void onButtonPress();

  std::vector<std::string> mStringList;
  int mStringChoice = 0;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
