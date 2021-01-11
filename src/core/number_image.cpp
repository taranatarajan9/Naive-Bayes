#ifndef NAIVE_BAYES_NUMBER_IMAGE_H
#define NAIVE_BAYES_NUMBER_IMAGE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <core/number_image.h>

#endif  // NAIVE_BAYES_NUMBER_IMAGE_H
using namespace std;

namespace numberimage{

NumberImage::NumberImage(vector<string> image) {
  image_ = image;
  label_ = -1;
}

NumberImage::NumberImage(vector<string> image, int label) {
  if (image.empty()) {
    throw std::invalid_argument("The vector provided is not a valid image");
  }
  image_ = image;
  label_ = label;
  side_length_ = image.at(0).length();
}

vector<string> NumberImage::GetImage() {
  return image_;
}
int NumberImage::GetLabel() {
  return label_;
}

int NumberImage::GetSideLength() {
  return side_length_;
}

string NumberImage::GetStringAt(int position) {
  return image_.at(position);
}

}// namespace numberimage