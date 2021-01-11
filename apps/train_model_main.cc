#include <core/naive_bayes_classifier.h>
#include <iostream>
#include <fstream>
#include <iostream>

using namespace naivebayes;
using namespace naivebayes::trainmodel;
using namespace naivebayes::classifier;

int main(int argc, char** argv) {
  TrainModel TrainOnImages;
  ImageSet new_set;
  ModelClassifier my_model;
  ImageSet test_images;
  bool test_only = strcmp(argv[1], "from_file") == 0;
  int subtract = 0;
  if (test_only) {
    subtract = 1;
  }

  if (argc > 2 && !test_only) { // train only
    new_set = ImageSet(argv[2]);
    ifstream train_images(argv[1]);
    train_images >> new_set;
    TrainOnImages = TrainModel(new_set);
  }

  if (argc > 3 && !test_only) { // train and save
    ofstream write_in;
    write_in.open(argv[3]);
    write_in << TrainOnImages;
  }

  if (argc > 5 || test_only) { // train, save, and get accuracy
                               // or get accuracy from file
    ifstream results;
    results.open(argv[3 - subtract]);
    results >> my_model;
//    my_model = ModelClassifier(TrainOnImages);
    test_images = ImageSet(argv[4 - subtract]);
    ifstream test;
    test.open(argv[5 - subtract]);
    test >> test_images;
    cout << my_model.GetAccuracy(test_images);
  }

  return 0;
}
