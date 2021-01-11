//
// Created by Tara Natarajan on 10/13/20.
//
#include <catch2/catch.hpp>

#include <core/naive_bayes_model.h>
using namespace naivebayes;
using namespace numberimage;

TEST_CASE("Test Number Image Functionality") {
  SECTION("Initialize 3 x 3 Image") {
    vector<string> three_by_three{"###", " # ", "## "};
    int label = 3;
    NumberImage three = NumberImage(three_by_three, label);
    REQUIRE(three.GetLabel() == label);
    REQUIRE(three.GetImage().at(1).compare(" # ") == 0);
  }

  SECTION("Initialize 5 x 5 Image") {
    vector<string> three_by_three{"#####", "#   ", "###  ", "   # ", "###  "};
    int label = 5;
    NumberImage three = NumberImage(three_by_three, label);
    REQUIRE(three.GetLabel() == label);
    REQUIRE(three.GetImage().at(3).compare("   # ") == 0);
  }

  SECTION("Initialize Empty Image") {
    vector<string> empty = {};
    int label = 0;
    REQUIRE_THROWS_AS(NumberImage(empty, label), std::invalid_argument);
  }
}