//
// Created by Tara Natarajan on 10/16/20.
//
#include <core/number_image.h>
#include <vector>
#ifndef NAIVE_BAYES_NUMBER_SET_H
#define NAIVE_BAYES_NUMBER_SET_H
using namespace std;
using namespace numberimage;
#endif  // NAIVE_BAYES_NUMBER_SET_H

namespace imageset {
class ImageSet {
 public:
  // Constructs an Empty Image Set
  ImageSet();

  // Constructs an Image Set from a given set of vector strings and labels
  // Formats the images and stores them as a vector of number images
  ImageSet(const vector<string>& image_lines, const vector<int>& labels);

  // Create an ImageSet with only labels
  ImageSet(const string& label_path);

  // Constructs a new Image Set from a vector of NumberImages
  ImageSet(vector<NumberImage> images);

  // Getter for Number of occurrences of a provided label
  int GetLabelCounts(int label);

  // Getter for the shaded positions of a given label
  vector<vector<int>>& GetShadedCounts(int label);

  // Gets an image in a certain index in the set
  NumberImage& GetImageAt(int index);

  // Get the label of an image in the set
  int GetLabelAt(int index);

  // Get the side length of the images being stored in the imageset
  int GetSideLength();

  // Get the total number of images from the set
  int GetNumberOfImages();

  // Count the number of times a spot is shaded for each position on the grid
  void SetCounts();

  // Overloads the >> operator to accept image sets
  friend istream &operator>>( istream  &input, ImageSet &set );

 private:
  map<int, vector<vector<int>>> shaded_count_; // stores counts of
                                               // the positions shaded for each label
  map<int, int> label_count_; // stores the number of occurrences of each label
  vector<NumberImage> image_set_; // stores the numberimages
  vector<int> labels_; // stores the labels
                       // (only used when labels and images are provided separately)
  int side_length_; // stores the side length of the image

  // Sets Labels from a specified filepath
  vector<int> SetLabels(const string& file_path);

  // Creates a vector of Number Images from a vector of image lines
  // and sets their labels from the vector of images
  vector<NumberImage> FormatImages(const vector<string>& image_lines, const vector<int>& image_labels);

  // Initializes Shaded and Label counts to vectors of zeros
  void InitializeNumberSet();

  // Creates a map with each label as a key and an
  // n x n vector of zeros as the value
  map<int, vector<vector<int>>> InitializeShadedCounts();

  //Creates a map with all values = 0
  map<int, int> InitializeLabelCounts();

  // Creates a vector of zeros
  // Uses the appropriate dimensions of the images provided
  // Returns the vector
  vector<vector<int>> CreateEmptyVector();

  // Adds to the count of shaded pixels for an individual image of a digit
  // based on which pixels are shaded in the provided image
  // added the appropriate vector in the shaded_count_ map
  void AddNumberImage(NumberImage image);
};
} // namespace numberimageset