//
// Created by Shalni Sundram on 4/19/20.
// Citation: This specific file is based off of the Basic sample in PretzelGui repo
// ** Not my work - using this sample as a reference for learning
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "shooter/enemy.h"
#include "shooter/game_engine.h"
#include <algorithm>
#include <iostream>

#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicSampleApp : public App {

 public:
  static void prepareSettings(Settings *settings);
  void setup() override;
  void mouseDown(MouseEvent event) override;
  void update() override;
  void draw() override;
  void keyDown(KeyEvent event) override;
  void DrawGun();
  void MoveGun();
  void MoveRight();
  void MoveLeft();

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
  float gun_x_pos;
  float gun_x_pos_two;
  bool hit_right;
  bool hit_left;

  size_t tile_size;
  vec2 mTopLeftCornerPos;
  vec2 mPosition;
  vec3 mVec3;

  bool bDrawOutline;
  bool bMakeEasy;
  bool bMakeMed;
  bool bMakeHard;
  string mFps;
  string mBubble;

  ci::ColorA mCol;
  void onButtonPress();

  std::vector<std::string> mStringList;
  int mStringChoice = 0;
};

void BasicSampleApp::setup() {
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
  gun_x_pos = getWindowWidth()*.5 + 30;
  gun_x_pos_two = gun_x_pos + 50;
  hit_left = false;
  hit_right = false;
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
  gui->addButton("Random Color", &BasicSampleApp::onButtonPress, this);
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

  //	gui->minimize();        // start in a minimized mode (same as double-clicking the top bar)

  ci::gl::enableAlphaBlending();
}

void BasicSampleApp::keyDown(KeyEvent event) {
  if (event.getChar() == 'g') {
    gui->toggleVisible();  // gui interaction will be disabled when invisible
  }
//  switch(event.getCode()) {
//    case KeyEvent::KEY_RIGHT: {
//      gun_x_pos +=
//    }
//  }
}

void BasicSampleApp::mouseDown(MouseEvent event) {}

void BasicSampleApp::onButtonPress() {
  mCol =
      ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
}

void BasicSampleApp::update() {
  time += .1;
  easySpeed += .3;
  medSpeed += .7;
  hardSpeed += 1;

//  while (bMakeEasy) {
//    MoveRight();
//    if (gun_x_pos_two == getWindowWidth()) {
//      cout << "hi" << endl;
//      while (gun_x_pos != 0) {
//        MoveLeft();
//      }
//    }
//  }

  MoveGun();

  if (bMakeEasy) {
    mTopLeftCornerPos.x += 1;
  } else if (bMakeMed) {
    mTopLeftCornerPos.x += 3;
  } else if (bMakeHard) {
    mTopLeftCornerPos.x += 4;
  }
  mFps = toString((int)getAverageFps());
}

void BasicSampleApp::draw() {

  gl::clear(Color(84. / 255., 166. / 255., 1));

  mCol.a = mOpacity;

  DrawGun();

  gl::color(mCol);
 // loop over enemies and draw enemy

 vector<shooter::Enemy> enemies = game_engine_.GetAllEnemies();
 for (int i = 0; i < enemies.size(); i++) {
   if(bMakeEasy) {
     gl::drawSolidCircle(mTopLeftCornerPos + sin(easySpeed) * 20, easyRadius);
   } else if (bMakeMed) {
     gl::drawSolidCircle(mTopLeftCornerPos + sin(medSpeed) * 2, medRadius);
   } else if(bMakeHard) {
     gl::drawSolidCircle(mTopLeftCornerPos + sin(hardSpeed) * 3, hardRadius);
   } else {
     gl::drawSolidCircle(mTopLeftCornerPos, easyRadius);
   }
 }

  if (bDrawOutline) {
    gl::drawStrokedCircle(mPosition + sin(time) * 7, mRadius);
  } else {
    gl::drawSolidCircle(mPosition + sin(time - 3) * 7, mRadius);
  }
  gl::drawString("< " + mBubble, mPosition + vec2(mRadius + 10, -10), mCol,
                 Font("Arial", 24));

  gui->draw();
}

void BasicSampleApp::DrawGun() {
  gl::drawSolidRect(Rectf(gun_x_pos, getWindowHeight() - 70, gun_x_pos_two, getWindowHeight()));
}

void BasicSampleApp::MoveGun() {
  cout << "Hello" << endl;
  if (gun_x_pos == 0) {
    hit_left = true;
    hit_right = false;
    MoveRight();
  } else if (gun_x_pos_two == getWindowWidth()) {
    hit_right = true;
    hit_left = false;
  }

  if (hit_left) {
    MoveRight();
  } else if (hit_right) {
    MoveLeft();
  } else {
    MoveRight();
  }
}

void BasicSampleApp::MoveRight() {
  gun_x_pos += 1;
  gun_x_pos_two += 1;
}

void BasicSampleApp::MoveLeft() {
  gun_x_pos -= 10;
  gun_x_pos_two -= 10;
}


CINDER_APP(BasicSampleApp, RendererGl, [](App::Settings* settings){
  settings->prepareWindow(Window::Format().size(1024, 768).title("PrezelGui :: BasicSample"));
  settings->setFrameRate(60.0f);
//	settings->setHighDensityDisplayEnabled();
})



