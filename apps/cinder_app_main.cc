#include <visualizer/carrom_app.h>


void prepareSettings(CarromApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(CarromApp, ci::app::RendererGl, prepareSettings);
