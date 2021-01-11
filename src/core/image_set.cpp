//
// Created by Tara Natarajan on 10/16/20.
//
#include <core/image_set.h>

#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace numberimage;

namespace imageset {
ImageSet::ImageSet() {
  side_length_ = 0;
}

ImageSet::ImageSet(const string& label_path) {
  labels_ = SetLabels(label_path);
  label_count_ = InitializeLabelCounts();
}

ImageSet::ImageSet(vector<NumberImage> images) {
  side_length_ = images.at(0).GetSideLength();
  image_set_ = images;
  InitializeNumberSet();
}

ImageSet::ImageSet(const vector<string>& image_lines, const vector<int>& labels) {
  side_length_ = image_lines.at(0).size();
  image_set_ = FormatImages(image_lines, labels);
  InitializeNumberSet();
}

int ImageSet::GetLabelCounts(int label) {
  if (label < 10 && label > -1) {
    return label_count_.at(label);
  }
  return 0;
}

vector<vector<int>>& ImageSet::GetShadedCounts(int label) {
  return shaded_count_.at(label);
}

NumberImage& ImageSet::GetImageAt(int index) {
  return image_set_.at(index);
}

int ImageSet::GetSideLength() {
  return side_length_;
}

int ImageSet::GetNumberOfImages() {
  return image_set_.size();
}

int ImageSet::GetLabelAt(int index) {
  return image_set_.at(index).GetLabel();
}

vector<int> ImageSet::SetLabels(const string& file_path) {
  vector<int> labels_pos;
  ifstream is(file_path);
  int x;
  while (is >> x) {
    labels_pos.push_back(x);  // read integer from file
  }

  return labels_pos;
}

void ImageSet::InitializeNumberSet() {
  label_count_ = InitializeLabelCounts();
  shaded_count_ = InitializeShadedCounts();
  SetCounts();
}

void ImageSet::SetCounts() {
  for (auto& current_image: image_set_) {
    AddNumberImage(current_image);
  }
}

void ImageSet::AddNumberImage(NumberImage image) {
  vector<string> image_data = image.GetImage();
  int label = image.GetLabel();

  vector<vector<int>> current_label = shaded_count_.at(label);
  label_count_[label]++;
  int row = 0;
  int column;
  char current;

  for (auto& current_string: image_data) {
    for (column = 0; column < side_length_; column++) {
      current = current_string.at(column);
      if (current != ' ') {
        shaded_count_.at(label).at(row).at(column)++;
      }
    }
    row++;
  }
}

map<int, vector<vector<int>>> ImageSet::InitializeShadedCounts() {
  map<int, vector<vector<int>>> shaded_count;
  int index;
  vector<vector<int>> empty = CreateEmptyVector();
  for (index = 0; index < 10; index ++) {
    shaded_count.insert(pair<int, vector<vector<int>>>(index, empty));
  }
  return shaded_count;
}

map<int, int> ImageSet::InitializeLabelCounts() {
  map<int, int> label_count;
  int index;
  vector<vector<int>> empty = CreateEmptyVector();
  for (index = 0; index < 10; index ++) {
    label_count.insert(pair<int,int>(index, 0));
  }
  return label_count;
}

vector<vector<int>> ImageSet::CreateEmptyVector() {
  vector<vector<int>> shaded_freq;
  vector<int> zeros(side_length_, 0);
  int y_value;
  for (y_value = 0; y_value < side_length_; y_value++) {
    shaded_freq.push_back(zeros);
  }

  return shaded_freq;
}

vector<NumberImage> ImageSet::FormatImages(const vector<string>& image_lines,
                                           const vector<int>& image_labels) {
  vector<NumberImage> images;
  vector<string> current;
  int row;
  int column;
  int index=0;
  for (row = 0; row < (image_labels.size()); row++) {
    for (column = 0; column < side_length_; column++) {
      current.push_back(image_lines[index]);
      index++;
    }
    images.push_back(numberimage::NumberImage(current, image_labels[row]));
    current.clear();
  }
  return images;
}

istream& operator>>(istream& input, ImageSet& I) {
  I.side_length_ = 0;
  string str;
  vector<string> data;
  while (!input.eof()) {
    while (getline(input, str)) {
      data.push_back(str);
      if (str.length() > I.side_length_) {
        I.side_length_ = str.length();
      }
    }
  }
  I = ImageSet(data, I.labels_);
  return input;
}

}  // namespace imageset