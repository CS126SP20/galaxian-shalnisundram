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

#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicSampleApp : public App {
 public:
  static void prepareSettings(Settings *settings);
  void setup() override;
  void mouseDown( MouseEvent event ) override;
  void update() override;
  void draw() override;
  void keyDown(KeyEvent event) override;

  pretzel::PretzelGuiRef gui;
  float mRadius;
  float mOpacity;
  float time;

  vec2 mPosition;
  vec3 mVec3;

  bool bDrawOutline;
  string mFps;
  string mBubble;

  ci::ColorA mCol;
  void onButtonPress();

  std::vector<std::string>    mStringList;
  int                         mStringChoice = 0;
};

void BasicSampleApp::setup()
{
  Rand::randomize();

  time = 0;
  mRadius = 25;
  mOpacity = 0.75;
  mPosition = getWindowCenter();
  bDrawOutline = false;
  mCol = Color::white();
  mBubble = "Hello, world!";

  mStringList = {"one", "two", "three"};

  gui = pretzel::PretzelGui::create("Circle settings");

  // Sliders can take ints, float, vec2, and vec3
  gui->addSlider("Position", &mPosition, vec2(0,0), getWindowSize());
  gui->addLabel("Other Settings");
  gui->addButton("Random Color", &BasicSampleApp::onButtonPress, this);
  gui->addToggle("Draw outline", &bDrawOutline);
  gui->addColorPicker("Circle Color", &mCol);

  // Passing floats will keep your sliders as floats
  gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
  gui->addSlider("Radius", &mRadius, 0, 100);

  // Textfields can be editable or non-editable
  gui->addTextField("FPS", &mFps, false);
  gui->addTextField("Speech Bubble", &mBubble, true);

  gui->addEnum("Choose", &mStringList, &mStringChoice);

  gui->addSaveLoad();

  gui->loadSettings();    // load the last saved settings automatically

  //	gui->minimize();        // start in a minimized mode (same as double-clicking the top bar)

  ci::gl::enableAlphaBlending();
}

void BasicSampleApp::keyDown(KeyEvent event)
{
  if (event.getChar() == 'g'){
    gui->toggleVisible();	// gui interaction will be disabled when invisible
  }
}

void BasicSampleApp::mouseDown( MouseEvent event )
{
}

void BasicSampleApp::onButtonPress()
{
  mCol = ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
}

void BasicSampleApp::update()
{
  time += .1;
  mFps = toString((int)getAverageFps());
}

void BasicSampleApp::draw()
{
  gl::clear(Color(84. / 255., 166. / 255., 1));

  mCol.a = mOpacity;

  gl::color(mCol);

  if (bDrawOutline){
    gl::drawStrokedCircle(mPosition + sin(time) * 7, mRadius);
  }else {
    gl::drawSolidCircle(mPosition + sin(time) * 7, mRadius);
  }
  gl::drawString("< " + mBubble, mPosition + vec2(mRadius + 10, -10), mCol, Font("Arial", 24));

  gui->draw();
}

CINDER_APP(BasicSampleApp, RendererGl, [](App::Settings* settings){
  settings->prepareWindow(Window::Format().size(1024, 768).title("PrezelGui :: BasicSample"));
  settings->setFrameRate(60.0f);
//	settings->setHighDensityDisplayEnabled();
})

