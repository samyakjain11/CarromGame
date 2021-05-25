#pragma once


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/carrom_game.h"

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class CarromApp: public ci::app::App {
 public:

  CarromApp();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double kWindowSize = 800;

 private:
  constexpr const static double kMargin_ = 50;
  constexpr const static double kSquareDim_ = 500;
  Game game_;
};

