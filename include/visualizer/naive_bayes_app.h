#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include <core/naive_bayes_classifier.h>
#include "cinder/gl/gl.h"
#include "sketchpad.h"

using namespace naivebayes::classifier;

namespace naivebayes {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class NaiveBayesApp : public ci::app::App {
 public:
  NaiveBayesApp();

  // Draws the sketchpad and a border around it
  void draw() override;
  // Shades a pixel when the user clicks on it
  void mouseDown(ci::app::MouseEvent event) override;
  // Shades a line of pixels when the user drags their mouse over it
  void mouseDrag(ci::app::MouseEvent event) override;
  // Displays a prediction for the drawing when the user clicks enter
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 875; // Number of pixels in the app
  const double kMargin = 100; // Number of pixels in the border
  const size_t kImageDimension = 28; // Number of 'pixels' in the image

 private:
  Sketchpad sketchpad_;
  int current_prediction_ = -1;
  ModelClassifier classifier_;

  void SetClassifier();
};

}  // namespace visualizer

}  // namespace naivebayes
