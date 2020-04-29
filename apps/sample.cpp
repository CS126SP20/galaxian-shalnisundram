//
// Created by Shalni Sundram on 4/19/20.
// Citation: This specific file is based off of the Basic sample in PretzelGui repo
// ** Not my work - using this sample as a reference for learning
//

//#include "cinder/app/App.h"
//#include "cinder/app/RendererGl.h"
//#include "cinder/gl/gl.h"
//#include "cinder/Rand.h"
//#include "cinder/CinderMath.h"
//#include "shooter/enemy.h"
//#include "shooter/game_engine.h"
//#include <algorithm>
//#include <iostream>
//#include "my_app.h"
//
//#include "pretzel/PretzelGui.h"
//
//using namespace ci;
//using namespace ci::app;
//using namespace std;
//
//class MyApp : public cinder::app::App {
//// public:
////  static void prepareSettings(Settings *settings);
////  void setup() override;
////  void mouseDown(MouseEvent event) override;
////  void update() override;
////  void draw() override;
////  void keyDown(KeyEvent event) override;
////  void DrawGun();
////  void DrawEnemies();
////  void MoveGun();
////  void MoveRight();
////  void MoveLeft();
////  void SetToggleSettings();
//
//  pretzel::PretzelGuiRef gui;
//
//  shooter::GameEngine game_engine_;
//  float mRadius;
//  float easyRadius;
//  float medRadius;
//  float hardRadius;
//  float mOpacity;
//  float time;
//  float easySpeed;
//  float medSpeed;
//  float hardSpeed;
//  int gun_x_pos;
//  int gun_x_pos_two;
//  bool hit_right_wall_;
//  bool hit_left_wall_;
//
//  size_t tile_size;
//  vec2 mTopLeftCornerPos;
//  vec2 mPosition;
//  vec2 enemy_position;
//  vec3 mVec3;
//
//  bool bDrawOutline;
//  bool bMakeEasy;
//  bool bMakeMed;
//  bool bMakeHard;
//  string mFps;
//  string mBubble;
//
//  ci::ColorA mCol;
//  void onButtonPress();
//
//  std::vector<std::string> mStringList;
//  int mStringChoice = 0;
//
//};
//
//void MyApp::setup() {
//  Rand::randomize();
//
//  time = 0;
//  easySpeed = 0;
//  medSpeed = 0;
//  hardSpeed = 0;
//  mRadius = 25;
//  easyRadius = 25;
//  medRadius = 10;
//  hardRadius = 5;
//  mOpacity = 0.75;
//  gun_x_pos = getWindowWidth()*.5 + 30;
//  gun_x_pos_two = gun_x_pos + 50;
//  hit_left_wall_ = false;
//  hit_right_wall_ = false;
//  mPosition = getWindowCenter();
//  mTopLeftCornerPos = getWindowPos();
//  bDrawOutline = false;
//  mCol = Color::white();
//  mBubble = "Hello, world!";
//
//  mStringList = {"one", "two", "three"};
//
//  gui = pretzel::PretzelGui::create("Circle settings");
//
//  // Sliders can take ints, float, vec2, and vec3
//  gui->addSlider("Position", &mPosition, vec2(0, 0), getWindowSize());
//  gui->addLabel("Other Settings");
//  gui->addButton("Random Color", &MyApp::onButtonPress, this);
//  gui->addToggle("Draw outline", &bDrawOutline);
//  gui->addToggle("Easy", &bMakeEasy);
//  gui->addToggle("Medium", &bMakeMed);
//  gui->addToggle("Hard", &bMakeHard);
//  gui->addColorPicker("Circle Color", &mCol);
//
//  // Passing floats will keep your sliders as floats
//  gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
//  gui->addSlider("Radius", &mRadius, 0, 100);
//
//  // Textfields can be editable or non-editable
//  gui->addTextField("FPS", &mFps, false);
//  gui->addTextField("Speech Bubble", &mBubble, true);
//
//  gui->addEnum("Choose", &mStringList, &mStringChoice);
//
//  gui->addSaveLoad();
//
//  gui->loadSettings();  // load the last saved settings automatically
//
//  ci::gl::enableAlphaBlending();
//}
//
//void MyApp::keyDown(KeyEvent event) {
//  if (event.getChar() == 'g') {
//    gui->toggleVisible();  // gui interaction will be disabled when invisible
//  }
////  switch(event.getCode()) {
////    case KeyEvent::KEY_RIGHT: {
////      gun_x_pos +=
////    }
////  }
//}
//
//void MyApp::mouseDown(MouseEvent event) {}
//
//void MyApp::onButtonPress() {
//  mCol =
//      ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
//}
//
//void MyApp::update() {
//  time += .1;
//  easySpeed += .3;
//  medSpeed += .7;
//  hardSpeed += 1;
//  enemy_position += 2;
//
//  SetToggleSettings();
//  MoveGun();
//
//  mFps = toString((int)getAverageFps());
//}
//
//void MyApp::draw() {
//
//  gl::clear(Color(84. / 255., 166. / 255., 1));
//
//  mCol.a = mOpacity;
//
//  DrawGun();
//
//  gl::color(mCol);
//
//  DrawEnemies();
//
//  if (bDrawOutline) {
//    gl::drawStrokedCircle(mPosition + sin(time) * 7, mRadius);
//  } else {
//    gl::drawSolidCircle(mPosition + sin(time - 3) * 7, mRadius);
//  }
//  gl::drawString("< " + mBubble, mPosition + vec2(mRadius + 10, -10), mCol,
//                 Font("Arial", 24));
//
//  gui->draw();
//}
//
//void MyApp::DrawEnemies() {
//  vector<shooter::Enemy> enemies = game_engine_.GetAllEnemies();
//  for (int i = 0; i < enemies.size(); i++) {
//    enemy_position = enemies[i].GetEnemyPosition();
//    if (bMakeEasy) {
//      gl::drawSolidCircle(enemy_position + sin(easySpeed) * 20, easyRadius);
//    } else if (bMakeMed) {
//      gl::drawSolidCircle(enemy_position + sin(medSpeed) * 2, medRadius);
//    } else if(bMakeHard) {
//      gl::drawSolidCircle(enemy_position + sin(hardSpeed) * 3, hardRadius);
//    } else {
//      gl::drawSolidCircle(mTopLeftCornerPos, easyRadius);
//    }
//  }
//}
//
//void MyApp::DrawGun() {
//  gl::drawSolidRect(Rectf(gun_x_pos, getWindowHeight() - 70, gun_x_pos_two, getWindowHeight()));
//}
//
//void MyApp::SetToggleSettings() {
//  if (bMakeEasy) {
//    mTopLeftCornerPos.x += 1;
//  } else if (bMakeMed) {
//    mTopLeftCornerPos.x += 3;
//  } else if (bMakeHard) {
//    mTopLeftCornerPos.x += 4;
//  }
//}
//
//void MyApp::MoveGun() {
//
//  // Check if gun hits the window's edge
//  if (gun_x_pos == 0) {
//    hit_left_wall_ = true;
//    hit_right_wall_ = false;
//    MoveRight();
//  } else if (gun_x_pos_two == getWindowWidth()) {
//    hit_right_wall_ = true;
//    hit_left_wall_ = false;
//  }
//
//  // Set direction depending on most recent wall hit
//  if (hit_left_wall_) {
//    MoveRight();
//  } else if (hit_right_wall_) {
//    MoveLeft();
//  } else {
//    MoveRight(); // Default
//  }
//}
//
//void MyApp::MoveRight() {
//  gun_x_pos += 1;
//  gun_x_pos_two += 1;
//}
//
//void MyApp::MoveLeft() {
//  gun_x_pos -= 10;
//  gun_x_pos_two -= 10;
//}
//
//
//CINDER_APP(MyApp, RendererGl, [](App::Settings* settings){
//  settings->prepareWindow(Window::Format().size(1024, 768).title("PrezelGui :: BasicSample"));
//  settings->setFrameRate(60.0f);
////	settings->setHighDensityDisplayEnabled();
//})
//
//

