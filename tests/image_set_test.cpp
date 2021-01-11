//
// Created by Tara Natarajan on 10/19/20.
//
#include <core/naive_bayes_model.h>

#include <catch2/catch.hpp>
#include <fstream>
using namespace naivebayes;
using namespace numberimage;

TEST_CASE("Initialize an Image Set of 3x3 images") {
  vector<string> three_by_three{" # ", " # ", " # ",
                                "+#+", "# #", "###",
                                " # ", "## ", " # "};
  vector<int> label{ 1, 0, 1};
  ImageSet NewModel = ImageSet(three_by_three, label);
  SECTION("Test that it will initialize") {
    SECTION("Test that side length is accurate") {
      REQUIRE(NewModel.GetSideLength() == 3);
    }
    SECTION("Test that labels are stored accurately") {
      REQUIRE(NewModel.GetLabelAt(0) == 1);
      REQUIRE(NewModel.GetLabelAt(2) == 1);
    }
    SECTION("Test that image strings are stored accurately") {
      REQUIRE(NewModel.GetImageAt(0).GetImage().at(2).compare(" # ") == 0);
      REQUIRE(NewModel.GetImageAt(1).GetImage().at(1).compare("# #") == 0);
      REQUIRE(NewModel.GetImageAt(2).GetImage().at(0).compare(" # ") == 0);
    }
  }

  SECTION("Test that counts are set accurately") {
    SECTION("Test that the labels are counted accurately") {
      REQUIRE(NewModel.GetLabelCounts(1) == 2);
      REQUIRE(NewModel.GetLabelCounts(9) ==0);
    }

    SECTION("Test that the shaded points are counted accurately") {
      REQUIRE(NewModel.GetShadedCounts(1).at(1).at(1) == 2); //test with multiple
      REQUIRE(NewModel.GetShadedCounts(0).at(2).at(1) == 1); //test for point with one shaded
      REQUIRE(NewModel.GetShadedCounts(4).at(0).at(2) == 0); //test for point without a label
    }
  }
}

TEST_CASE("Initialize a set of 5 X 5 Images") {
  vector<string> five_by_five{"  #  "," # # ","   # "," #   ","#####",
                              " ##  ","#  # ","  ## ","    #"," ####"};
  vector<int> label{2,3};
  ImageSet NewModel = ImageSet(five_by_five, label);
  SECTION("Test that it will initialize") {
    SECTION("Test that side length is accurate") {
      REQUIRE(NewModel.GetSideLength() == 5);
    }
    SECTION("Test that labels are stored accurately") {
      REQUIRE(NewModel.GetLabelAt(0) == 2);
      REQUIRE(NewModel.GetLabelAt(1) == 3);
    }
    SECTION("Test that the strings for each image are stored correctly") {
      REQUIRE(NewModel.GetImageAt(1).GetImage().at(0).compare(" ##  ") == 0);
      REQUIRE(NewModel.GetImageAt(0).GetImage().at(3).compare(" #   ") == 0);
    }
  }

  SECTION("Test that the counts are set accurately") {
    SECTION("Test that the labels are accurately counted") {
      REQUIRE(NewModel.GetLabelCounts(3) == 1);
      REQUIRE(NewModel.GetLabelCounts(7) ==0);
    }

    SECTION("Test that each position's shaded count is accurate") {
      REQUIRE(NewModel.GetShadedCounts(2).at(1).at(1) == 1);
      REQUIRE(NewModel.GetShadedCounts(6).at(3).at(2) == 0);
    }
  }
}

TEST_CASE("Test Derivation of ImageSet from files") {
  string image_file = "/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/test_images.txt";
  string labels_file = "/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/test_labels.txt";
  ImageSet images = ImageSet(labels_file);
  ifstream file(image_file);
  file >> images;
  SECTION("Test that the model was properly initialized") {
    SECTION("Test that side length is stored properly") {
      REQUIRE(images.GetSideLength() == 5);
    }
    SECTION("Test that the model stores labels accurately") {
      vector<int>labels{0, 3, 1, 7, 8, 9, 8, 8};
      REQUIRE( images.GetLabelAt(3) == labels.at(3));
    }
    SECTION("Test that image strings are stored accurately") {
      REQUIRE(images.GetImageAt(1).GetImage().at(0).compare(" ####") == 0);
      REQUIRE(images.GetImageAt(3).GetImage().at(3).compare("  #  ") == 0);
      REQUIRE(images.GetImageAt(7).GetImage().at(3).compare("   # ") == 0);
    }
  }
  SECTION("Test that the model was trained properly") {
    SECTION("Test that the count of occurrences was stored accurately") {
      REQUIRE(images.GetLabelCounts(8)==4);
      REQUIRE(images.GetLabelCounts(7)==2);
      REQUIRE(images.GetLabelCounts(2)==0);
    }
    SECTION("Test that the count of shading at individual points is accurate") {
      REQUIRE(images.GetShadedCounts(8).at(2).at(3) == 4);
      REQUIRE(images.GetShadedCounts(3).at(0).at(3) == 3);
      REQUIRE(images.GetShadedCounts(4).at(0).at(3) == 0);
      REQUIRE(images.GetShadedCounts(2).at(2).at(2) == 0);
    }
  }
}

