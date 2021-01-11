#include <core/naive_bayes_model.h>
#include <iostream>
#include <fstream>
#include <string>

namespace naivebayes {
namespace trainmodel {
TrainModel::TrainModel(const vector<string>& images, const vector<int>& labels) {
  side_length_ = images.at(0).length();
  image_labels_ = labels;
  images_ = ImageSet(images, labels);
  Train();
}

TrainModel::TrainModel(int side_length, const map<int, double>& label_percentages,
                       const map<int, vector<vector<double>>>& point_percentages) {
  side_length_ = side_length;
  label_percentages_ = label_percentages;
  shaded_percentages_ = point_percentages;
}

TrainModel::TrainModel(const string &label_path) {
  image_labels_ = OpenLabels(label_path);
}

TrainModel::TrainModel(ImageSet image_set) {
  images_ = image_set;
  side_length_ = image_set.GetSideLength();
  Train();
}

TrainModel::TrainModel() {
  side_length_ = 0;
}

TrainModel::TrainModel(int side_length) {
  side_length_ = side_length;
}

bool TrainModel::Train() {
  vector<vector<double>> shaded;
  double label_percent;
  for (int label = 0; label < kMaxLabel; label++) {
    shaded = CalculatePercentages(label);
    shaded_percentages_.insert(
        pair<int, vector<vector<double>>>(label, shaded));
    label_percent = static_cast<double>(images_.GetLabelCounts(label)) /
                    (images_.GetNumberOfImages());
    label_percentages_.insert(pair<int, double>(label, label_percent));
  }
  return true;
}

istream &operator>>(istream &input, TrainModel &T) {
  T.side_length_ = 0;
  string str;
  vector<string> data;
  while (!input.eof()) {
    while (getline(input, str)) {
      data.push_back(str);
      if (str.length() > T.side_length_) {
        T.side_length_ = str.length();
      }
    }
  }
  T.images_ = ImageSet(data, T.image_labels_);
  T.Train();
  return input;
}

ostream &operator<<(ostream &output, TrainModel &T) {
  vector<vector<int>> shaded_positions;
  output << T.GetSideLength();
  output << "\n";
  for (int label = 0; label < T.kMaxLabel; label++) {
    output << label << " ";
    output << "\n";
    output << T.label_percentages_.at(label);
    output << "\n";
    for (auto &&current_row : T.shaded_percentages_.at(label)) {
      for (auto &&current_pos : current_row) {
        output << current_pos << " ";
      }
      output << "\n";
    }
  }

  return output;
}

int TrainModel::GetLabelCount(int label) {
  return images_.GetLabelCounts(label);
}

vector<vector<int>> TrainModel::GetShadedCount(int label) {
  return images_.GetShadedCounts(label);
}

int TrainModel::GetSideLength() {
  return side_length_;
}

NumberImage TrainModel::GetImageAt(int index) {
  return images_.GetImageAt(index);
}

vector<int> TrainModel::GetLabels() {
  return image_labels_;
}

double TrainModel::GetLabelPercentage(int label) {
  return label_percentages_.at(label);
}

vector<vector<double>> TrainModel::GetShadedPercentage(int label) {
  return shaded_percentages_.at(label);
}

vector<int> TrainModel::OpenLabels(const string &labels_path) {
  vector<int> labels_pos;
  ifstream is(labels_path);
  int x;
  while (is >> x) {
    labels_pos.push_back(x);  // read integer from file
  }

  return labels_pos;
}

vector<vector<double>> TrainModel::CalculatePercentages(int label) {
  vector<vector<int>> shaded_positions;
  vector<vector<int>> shaded_counts;
  vector<double> shaded_percentages;
  vector<vector<double>> shaded_image;
  double percentage;
  int count;

  shaded_counts = images_.GetShadedCounts(label);
  count = images_.GetLabelCounts(label);
  for (auto &&current_row : shaded_counts) {
    for (auto &&current_pos : current_row) {
      percentage =
          static_cast<double>(current_pos + kKValue) / (count + kKValue);
      shaded_percentages.push_back(percentage);
    }
    shaded_image.push_back(shaded_percentages);
    shaded_percentages.clear();
  }
  return shaded_image;
}
} //namespace train model
} // namespace naivebayes