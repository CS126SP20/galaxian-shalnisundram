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
  void DrawEnemies();
  void MoveGun();
  void MoveRight();
  void MoveLeft();
  void SetToggleSettings();

 public:
  pretzel::PretzelGuiRef gui;

  shooter::GameEngine game_engine_;
  float mRadius;
  float easyRadius;
  float medRadius;
  float hardRadius;
  float mOpacity;
  float time;
  float easySpeed;
  float medSpeed;
  float hardSpeed;
  float right_window_edge_;
  float left_window_edge_;
  float gun_x_pos;
  float gun_x_pos_two;

  bool bDrawOutline;
  bool bMakeEasy;
  bool bMakeMed;
  bool bMakeHard;
  bool hit_right_wall_;
  bool hit_left_wall_;

  vec2 mTopLeftCornerPos;
  vec2 mPosition;
  vec2 enemy_position;

  string mFps;
  string mBubble;

  ci::ColorA mCol;
  void onButtonPress();

  std::vector<std::string> mStringList;
  int mStringChoice = 0;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
