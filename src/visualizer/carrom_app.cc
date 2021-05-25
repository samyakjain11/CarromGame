#include <visualizer/carrom_app.h>

CarromApp::CarromApp() : game_(600, 50) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}


void CarromApp::update() {
  game_.Update();
}

void CarromApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color);

  ci::gl::drawStringCentered(
      "Use up/down arrow to increase/decrease velocity of your striker. Use"
      "left/right arrow key to adjust the striking angle counterclock-wise/clock-wise",
      glm::vec2(kWindowSize / 2, kMargin_ / 2),
      ci::Color("white"));
  ci::gl::drawStringCentered(
      "use wasd to move your striker along the board",
      glm::vec2(kWindowSize / 2, kSquareDim_ + 9 * kMargin_ / 2));

  game_.Draw();
}

void CarromApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_a:
      game_.UpdateStrikerLocation({-5, 0});
      break;
    case ci::app::KeyEvent::KEY_d:
      game_.UpdateStrikerLocation({5, 0});
      break;
    case ci::app::KeyEvent::KEY_UP:
      game_.UpdateStrikerProperties(0, 5);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      game_.UpdateStrikerProperties(0, -5);
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      game_.UpdateStrikerProperties(-5, 0);
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      game_.UpdateStrikerProperties(5, 0);
      break;
    case ci::app::KeyEvent::KEY_SPACE:
      game_.Launch();
      break;
  }
}

