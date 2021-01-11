//
// Created by Tara Natarajan on 10/18/20.
//
#include <core/naive_bayes_classifier.h>
#include <sstream>
#include <math.h>
using namespace naivebayes;
namespace naivebayes {
namespace classifier {
ModelClassifier::ModelClassifier() {
  model_ = TrainModel();
}

ModelClassifier::ModelClassifier(TrainModel model) {
  model_ = model;
}

void ModelClassifier::SetModel(TrainModel model) {
  model_ = model;
}

double ModelClassifier::GetAccuracy(ImageSet images) {
  int correct = 0;
  int total = images.GetNumberOfImages();
  if (total == 0) {
    return 0.0;
  }

  int current_index;
  vector<string> current_image;
  int current_label;
  int prediction;
  for (current_index = 0; current_index < total; current_index++) {
    current_image = images.GetImageAt(current_index).GetImage();
    current_label = images.GetImageAt(current_index).GetLabel();
    prediction = Classify(current_image);
    if (prediction == current_label) {
      correct ++;
    }
  }

  return static_cast<double>(correct) / (total);
}

int ModelClassifier::Classify(vector<vector<size_t>> points) {
  vector<string> image = EmptyImage(model_.GetSideLength());
  int row;
  int col;
  for (auto& point: points) {
    row = static_cast<int>(point.at(0));
    col = static_cast<int>(point.at(1));
    image.at(row)[col] = '#';
  }
  return Classify(image);
}

int ModelClassifier::Classify(const vector<string>& image) {
  int label = 0;
  double max_percentage = -1.0;
  double current_percentage;
  if (image.size() != model_.GetSideLength()) {
    return -1;
  }
  for (int potential_label = 0; potential_label < 10; potential_label++) {
    current_percentage = CalculateProbability(image, potential_label);
    if (current_percentage > max_percentage) {
      label = potential_label;
      max_percentage = current_percentage;
    }
  }
  return label;
}

double ModelClassifier::CalculateProbability(const vector<string>& image, int label) {
  double probability = model_.GetLabelPercentage(label);
  vector<vector<double>> shaded_percentages =
      model_.GetShadedPercentage(label);
  int row_num;
  int position;
  int side_length = shaded_percentages.size();
  char point;
  string line;
  vector<double> shaded_line;
  double point_prob;
  for (row_num = 0; row_num < side_length; row_num++) {
    line = image.at(row_num);
    shaded_line = shaded_percentages.at(row_num);
    for (position = 0; position < side_length; position++) {
      point = line.at(position);
      if (point == ' ') {
        point_prob = 1 - shaded_line.at(position);
      } else {
        point_prob = shaded_line.at(position);
      }
      probability = probability * point_prob;
    }
  }

  return probability;
}

istream& operator>>(istream& input, ModelClassifier& M) {
  int side_length;
  int count = 0;
  double percentage;
  map<int, double> label_percentages;
  map<int, vector<vector<double>>> labeled_shaded_per;
  vector<vector<double>> shaded_percentages;
  vector<double> shaded_line;
  int label;
  string line;
  input >> line;
  stringstream(line) >> side_length;
  bool has_zero = false;

  while (!input.eof()) {
    if (count == 0) {
      input >> label;
      if (has_zero && label == 0) {
        label = 1;
      }
    } else if (count == 1) {
      input >> percentage;
      label_percentages.insert(pair<int, double>(label, percentage));
    } else {
      if (shaded_line.size() == side_length) {
        shaded_percentages.push_back(shaded_line);
        shaded_line.clear();
        if (shaded_percentages.size() == side_length) {
          labeled_shaded_per.insert(
              pair<int, vector<vector<double>>>(label, shaded_percentages));
          shaded_percentages.clear();
          count = -1;
          has_zero = true;
        }
      }
      input >> percentage;
      shaded_line.push_back(percentage);
    }
    count++;
  }

  TrainModel newModel =
      TrainModel(side_length, label_percentages, labeled_shaded_per);

  M.SetModel(newModel);
  return input;
}

vector<string> ModelClassifier::EmptyImage(int side_length) {
  vector<string> empty;
  int row;
  string blanks(side_length, ' ');
  for(row = 0; row < side_length; row++) {
    empty.push_back(blanks);
  }

  return empty;
}

} //namespace classifier
} //namespace naivebayes