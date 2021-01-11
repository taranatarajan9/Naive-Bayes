#include <catch2/catch.hpp>
#include <fstream>
#include <core/naive_bayes_model.h>
using namespace naivebayes::trainmodel;

TEST_CASE("Train on a 3 X 3 Image") {
  vector<string> three_by_three{" # ", " # ", " # ",
                                "+#+", "# #", "###",
                                " # ", "## ", " # ",
                                " # ", "# #", "###",
                                "###", "  #", "###",
                                "# #", "###", "  #",};
  vector<int> labels{ 1, 0, 1, 2, 2, 4};
  ImageSet threexthree = ImageSet(three_by_three, labels);
  TrainModel NewModel = TrainModel(threexthree);

  SECTION("Test that the model is trained correctly") {
    SECTION("Test that the labels are distributed accurately") {
      REQUIRE(NewModel.GetLabelPercentage(7) - 0.1667 < 0.1); // test label with one occurrence
      REQUIRE(NewModel.GetLabelPercentage(1) - 0.333 < 0.1 ); // test label with multiple occurences
      REQUIRE(NewModel.GetLabelCount(9) == 0); // test label with zero occurrences
    }

    SECTION("Test that the shaded points are distributed accurately") {
      REQUIRE(NewModel.GetShadedPercentage(1).at(1).at(0) - 0.6667 < 0.1); // test with multiple
      REQUIRE(NewModel.GetShadedCount(4).at(2).at(2) - 1 < 0.1); // test for point once shaded
      REQUIRE(NewModel.GetShadedCount(4).at(0).at(1) < 0.1); //test for point with none shaded
      REQUIRE(NewModel.GetShadedCount(8).at(0).at(2)  < 0.1); //test for point without a label
    }
  }
}

TEST_CASE("Train on a 5 X 5 Image") {
  vector<string> five_by_five{"  #  ", " # # ", "   # ", " #   ", "#####",
                              "#####", "    #", " ####", "    #", "#####",
                              "#####", "   # ", "  ## ", "  #  ", " #   ",
                              " ##  ", "#  # ", "  ## ", "    #", " ####",
                              "#####", "#   #", "#####", "    #", "#####",
                              " ### ", "#   #", "#####", "#   #", " ### ",
                              " ####", "   # ", "  ###", "    #", " ### "};
  vector<int> label{2, 3, 7, 3, 9, 8, 3};
  TrainModel NewModel = TrainModel(five_by_five, label); // use vectors in constructor
                                                         // instead of imageset
  NewModel.Train();

  SECTION("Test that the model is trained") {
    SECTION("Test that the labels are accurately distributed") {
      REQUIRE(NewModel.GetLabelPercentage(3) - 0.4285 < 0.1); // check label with multiple
      REQUIRE(NewModel.GetLabelPercentage(7) - 0.1428 < 0.1); // check label with one
      REQUIRE(NewModel.GetLabelPercentage(5) < 0.1); // check label with none
    }

    SECTION("Test that each position's shaded count is accurate") {
      REQUIRE(NewModel.GetShadedPercentage(3).at(0).at(4) - 0.75 < 0.1); // check point with multiple shaded
      REQUIRE(NewModel.GetShadedPercentage(7).at(3).at(2) - 1 < 0.1); // check point once shaded
      REQUIRE(NewModel.GetShadedPercentage(9).at(3).at(3) - 1 < 0.1); // check point with none shaded
      REQUIRE(NewModel.GetShadedPercentage(6).at(3).at(2) - 1< 0.1); // check point with no occurrences of label
    }
  }
}

TEST_CASE("Test training of images from file") {
  string image_file = "/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/test_images.txt";
  string labels_file = "/Users/taranatarajan/cinder_0.9.2_mac/my-projects/naivebayes-taranatarajan9/data/test_labels.txt";
  TrainModel NewModel = TrainModel(labels_file);
  ifstream file(image_file);
  file >> NewModel;
  SECTION("Test that the model was trained properly") {
    SECTION("Test that the percentage of occurrences was stored accurately") {
      REQUIRE(NewModel.GetLabelPercentage(8) - 0.2666 < 0.1); // check multiple occurrences
      REQUIRE(NewModel.GetLabelPercentage(4) - 0.0666 < 0.1); // check single occurrence
      REQUIRE(NewModel.GetLabelPercentage(2) < 0.1); // check zero occurrences
    }
    SECTION("Test that the percentage of shading at individual points is accurate") {
      REQUIRE(NewModel.GetShadedPercentage(8).at(2).at(3) - 1 < 0.1); // check multiple shading and multiple occurrences
      REQUIRE(NewModel.GetShadedPercentage(3).at(2).at(4) - 0.5 < 0.1); // check single shading and multiple occurrences
      REQUIRE(NewModel.GetShadedPercentage(7).at(4).at(0) - 0.333 < 0.1); // check zero shading and multiple occurrences
      REQUIRE(NewModel.GetShadedPercentage(1).at(4).at(1) - 1 < 0.1); // check single shading and single occurrence
      REQUIRE(NewModel.GetShadedPercentage(0).at(2).at(2) - 0.5 < 0.1); // check zero shading and single occurrence
      REQUIRE(NewModel.GetShadedPercentage(2).at(0).at(3) - 1 < 0.1); // check zero occurrence
    }
  }
}

