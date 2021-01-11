#ifndef NAIVE_BAYES_NUMBER_IMAGE_H
#define NAIVE_BAYES_NUMBER_IMAGE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#endif  // NAIVE_BAYES_NUMBER_IMAGE_H
using namespace std;
namespace numberimage{
// Creates an image from strings
class NumberImage {
 public:
  // Constructor that stores a string of vectors as the image
  // and the label that represents it
  NumberImage(vector<string> image, int label);

  NumberImage(vector<string> image);

  NumberImage(vector<vector<size_t>> points, int side_length);
  // Returns the image stored in the vector
  vector<string> GetImage();

  // Returns the label of the image
  int GetLabel();

  // Returns the side length of the imgae
  int GetSideLength();

  //returns the string at a location of the image
  string GetStringAt(int position);

 private:
  vector<string> image_; // Vector representing the lines og the image "pixels"
  int label_; // Stores the label of the image
  int side_length_; // Side Length of the square image
};
}// namespace numberimage