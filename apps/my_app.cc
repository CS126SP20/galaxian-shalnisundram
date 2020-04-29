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
  easySpeed = 0;
  medSpeed = 0;
  hardSpeed = 0;
  mRadius = 25;
  easyRadius = 25;
  medRadius = 10;
  hardRadius = 5;
  mOpacity = 0.75;
  right_window_edge_ = 1022;
  left_window_edge_ = 2;
  gun_x_pos = getWindowWidth() * .5 + 30;
  gun_x_pos_two = gun_x_pos + 50;
  hit_left_wall_ = false;
  hit_right_wall_ = false;
  mPosition = getWindowCenter();
  mTopLeftCornerPos = getWindowPos();
  bDrawOutline = false;
  mCol = Color::white();
  mBubble = "Hello, world!";

  mStringList = {"one", "two", "three"};

  gui = pretzel::PretzelGui::create("Circle settings");

  // Sliders can take ints, float, vec2, and vec3
  gui->addSlider("Position", &mPosition, vec2(0, 0), getWindowSize());
  gui->addLabel("Other Settings");
  gui->addButton("Random Color", &MyApp::onButtonPress, this);
  gui->addToggle("Draw outline", &bDrawOutline);
  gui->addToggle("Easy", &bMakeEasy);
  gui->addToggle("Medium", &bMakeMed);
  gui->addToggle("Hard", &bMakeHard);
  gui->addColorPicker("Circle Color", &mCol);

  // Passing floats will keep your sliders as floats
  gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
  gui->addSlider("Radius", &mRadius, 0, 100);

  // Textfields can be editable or non-editable
  gui->addTextField("FPS", &mFps, false);
  gui->addTextField("Speech Bubble", &mBubble, true);

  gui->addEnum("Choose", &mStringList, &mStringChoice);

  gui->addSaveLoad();

  gui->loadSettings();  // load the last saved settings automatically

  ci::gl::enableAlphaBlending();

  game_engine_.InitializeEnemies();
}

void MyApp::keyDown(KeyEvent event) {
  if (event.getChar() == 'g') {
    gui->toggleVisible();  // gui interaction will be disabled when invisible
  }
  switch(event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      MoveRight();
    }
    case KeyEvent::KEY_LEFT : {
      MoveLeft();
    }
  }
}

void MyApp::mouseDown(MouseEvent event) {}

void MyApp::onButtonPress() {
  mCol =
      ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
}

void MyApp::update() {

  time += .1;
  easySpeed += .3;
  medSpeed += .7;
  hardSpeed += 1;
  //enemy_position += 2;
  enemy_position.x += 2;
  mPosition.x += 2;
  mPosition.x = mPosition.x + sin(time) * 7;

  // Moves enemy in a sin motion
  vector<shooter::Enemy> *these_enemies = game_engine_.GetAllEnemies();
  for (int i = 0; i < these_enemies -> size(); i++) {
    vec2 this_position = (*these_enemies)[i].GetEnemyPosition();
    this_position.x += sin(time) * 7;
    (*these_enemies)[i].SetEnemyPosition(this_position);
  }

  MoveGun();

  mFps = toString((int)getAverageFps());
}

void MyApp::draw() {
  gl::clear(Color(84. / 255., 166. / 255., 1));

  mCol.a = mOpacity;

  DrawGun();

  gl::color(mCol);

  DrawEnemies();

  if (bDrawOutline) {
    gl::drawStrokedCircle(mPosition + sin(time) * 7, mRadius);
  } else {
    gl::drawSolidCircle(mPosition + sin(time - 3) * 7, mRadius);
  }
  gl::drawString("< " + mBubble, mPosition + vec2(mRadius + 10, -10), mCol,
                 Font("Arial", 24));

  gui->draw();
}

void MyApp::DrawEnemies() {
  vector<shooter::Enemy> *enemies = game_engine_.GetAllEnemies();
  for (int i = 0; i < enemies->size(); i++) {
    enemy_position = (*enemies)[i].GetEnemyPosition();
    if (bMakeEasy) {
      gl::drawSolidCircle(enemy_position, easyRadius);
    } else if (bMakeMed) {
      gl::drawSolidCircle(enemy_position, medRadius);
    } else if (bMakeHard) {
      gl::drawSolidCircle(enemy_position, hardRadius);
    } else {
      gl::drawSolidCircle(enemy_position, easyRadius);
    }
  }
}

void MyApp::DrawGun() {
  gl::drawSolidRect(Rectf(gun_x_pos, getWindowHeight() - 70, gun_x_pos_two,
                          getWindowHeight()));
}

void MyApp::MoveGun() {

  // Check if gun hits the window's edge
  if (gun_x_pos == left_window_edge_) {
    hit_left_wall_ = true;
    hit_right_wall_ = false;
    MoveRight();
  } else if (gun_x_pos_two == right_window_edge_) {
    hit_right_wall_ = true;
    hit_left_wall_ = false;
  }

  // Set direction depending on most recent wall hit
  if (hit_left_wall_) {
    MoveRight();
  } else if (hit_right_wall_) {
    MoveLeft();
  } else {
    MoveRight();  // Default
  }
}

void MyApp::MoveRight() {
  gun_x_pos += 10;
  gun_x_pos_two += 10;
}

void MyApp::MoveLeft() {
  gun_x_pos -= 10;
  gun_x_pos_two -= 10;
}
} // namespace myapp

CINDER_APP(myapp::MyApp, RendererGl, [](App::Settings* settings){
  settings->prepareWindow(Window::Format().size(1024, 768).title("PrezelGui :: BasicSample"));
  settings->setFrameRate(60.0f);
//	settings->setHighDensityDisplayEnabled();
})
