//
// Created by Tara Natarajan on 10/19/20.
//
#include <core/naive_bayes_classifier.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>

using namespace naivebayes;
using namespace naivebayes::trainmodel;
using namespace naivebayes::classifier;

TEST_CASE("Classify from Existing TrainModel") {
  TrainModel my_model = TrainModel("/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/trainlabels");
  ifstream images;
  images.open("/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/trainimages.txt");
  images >> my_model;
  vector<string> three = {" ####", "   # ", "  #  ", "   # ", "###  "};
  vector<string> zero = {" ### ", "#   #", "#   #", "#   #", " ### "};
  vector<string> six = {"#####", "#    ", "#####", "#   #", "#####"};
  ModelClassifier classifier = ModelClassifier(my_model);

  SECTION("Check if probabilities are calculated accurately") {
    REQUIRE(classifier.CalculateProbability(three, 3) - 3.4304e-06 < 0.1);
    REQUIRE(classifier.CalculateProbability(zero, 0) - 6.42475e-06 < 0.1);
  }
  SECTION("Check that the correct label is more likely than a random number"){
    REQUIRE(classifier.CalculateProbability(three, 3)
            > classifier.CalculateProbability(three, 9));
    REQUIRE(classifier.CalculateProbability(zero, 0)
            > classifier.CalculateProbability(zero, 4));
    REQUIRE(classifier.CalculateProbability(six, 6)
            > classifier.CalculateProbability(six, 7));
    REQUIRE(classifier.CalculateProbability(six, 6) - 0.000912712 < 0.1);
  }

  SECTION("Check if Images are Classified Properly") {
    REQUIRE(classifier.Classify(three) == 3);
    REQUIRE(classifier.Classify(zero) == 0);
    REQUIRE(classifier.Classify(six) == 6);
  }
}

TEST_CASE("Classify from File") {
  ModelClassifier classifier;
  ifstream result_data;
  result_data.open("/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/test_results.txt");
  result_data >> classifier;

  vector<string> five = {"+####", "#    ", "+####", "    #", "####+"};
  vector<string> eight = {" ### ", "#   #", "#####", "#   #" , " ### "};
  vector<string> two = {" ####", "    #", " ### ", "#    ", "#####"};

  SECTION("Check if probabilities are calculated accurately") {
    REQUIRE(classifier.CalculateProbability(five, 5) - 0.000205592 < 0.001);
    REQUIRE(classifier.CalculateProbability(eight, 8) - 3.90616e-05 < 0.001);
  }

  SECTION("Check that the model predicts that the correct "
      "label is more likely than an arbitrary value") {
    REQUIRE(classifier.CalculateProbability(five, 5) >
            classifier.CalculateProbability(five, 0));
    REQUIRE(classifier.CalculateProbability(two, 2) >
            classifier.CalculateProbability(two, 4));
  }

  SECTION("Check if Images are Classified Properly") {
    REQUIRE(classifier.Classify(two) == 2);
    REQUIRE(classifier.Classify(five) == 5);
    REQUIRE(classifier.Classify(eight) == 8);
  }
}
