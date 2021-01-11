//
// Created by Tara Natarajan on 10/18/20.
//

#ifndef NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H

#endif  // NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H
#include <core/naive_bayes_model.h>
using namespace naivebayes::trainmodel;

namespace naivebayes {

namespace classifier {
class ModelClassifier {
 public:
  // Default constructor for Model Classifier
  // Stores no state just used for declaring
  // so the user can update later
  ModelClassifier();

  // Creates a classifier from the trained model provided
  ModelClassifier(TrainModel model);

  // Allows the user to set a new model to use to classify
  // without creating a new instance
  void SetModel(TrainModel model);

  // Calculates the accuracy of the model on a test set of images
  double GetAccuracy(ImageSet images);

  // Classifies an image as a certain number
  // based on whichever provides the highest probability
  int Classify(const vector<string>& image);

  // Calls the classify function but takes a set of shaded points
  // and converts it to a vector string format before classifying
  int Classify(vector<vector<size_t>> points);

  // Overloads the istream operator in order
  // to allow the user to load a model into the classification
  friend istream &operator>>(istream &input, ModelClassifier &M);

  // Calculates probability of the given image belonging to the specified label
  double CalculateProbability(const vector<string>& image, int label);

 private:
  TrainModel model_; // stores the trained model

  // creates an Empty Image that will be updated with the size_t points
  vector<string> EmptyImage(int side_length);
};
} //namespace classifier
} //namespace naive bayes