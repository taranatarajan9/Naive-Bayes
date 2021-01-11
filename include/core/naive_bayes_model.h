#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <core/image_set.h>
using namespace std;
using namespace imageset;

namespace naivebayes {
namespace trainmodel {
// Creates a Naive Bayes Model
class TrainModel {
 public:
  // Creates an instance of train model using file paths
  // for the images and its labels
  //  TrainModel(const string& image_path,const string& labels_path);

  TrainModel(const string &label_path);

  TrainModel();

  TrainModel(ImageSet image_set);

  TrainModel(int side_length);
  // Creates an instance of train model using vectors
  // for the number images and the labels
  // This was only created for testing
  TrainModel(const vector<string>& images, const vector<int>& labels);

  TrainModel(int side_length, const map<int, double>& label_percentages,
             const map<int, vector<vector<double>>>& point_percentages);

  // Trains the model by counting and storing
  // the occurrences of shading at each point in each image
  // Each model can only be trained once
  bool Train();

  // Getter for the side length of the image
  int GetSideLength();

  // Getter to represent the labels provided in the constructor
  vector<int> GetLabels();

  // Getter for the count of each label in the dataset
  // Does not contain information before the model is trained
  int GetLabelCount(int label);

  // Returns the NumberImage stored in the ImageSet
  NumberImage GetImageAt(int index);

  // Getter for the map representing the occurrences
  // of shading in each point for each possible digit
  // Does not contain information before the model is trained
  vector<vector<int>> GetShadedCount(int label);

  double GetLabelPercentage(int label);

  vector<vector<double>> GetShadedPercentage(int label);

  //  void SetSideLength(int length);

  // Returns every individual string from the file
  friend istream &operator>>(istream &input, TrainModel &T);

  // Returns a file with the information I need
  friend ostream &operator<<(ostream &output, TrainModel &T);

 private:
  int kMaxLabel = 10;
  int kKValue = 1;   // Represents the K value for Naive Bayes Calculation
  int side_length_;  // Represents the side length of images given
  vector<int> image_labels_;            // Stores the set of labels
  ImageSet images_;                     // Stores the images as a NumberImage
  map<int, double> label_percentages_;  // Stores the percentage of
                                        // each digit in the dataset
  map<int, vector<vector<double>>>
      shaded_percentages_;  // Stores the percentage of the times a
                            // point in the image is shaded
                            // for every digit

  // Returns a one dimensional vector of every label
  // from the text file in the provided path
  vector<int> OpenLabels(const string &labels_path);

  vector<vector<double>> CalculatePercentages(int label);
};
} // namespace trainmodel
}  // namespace naivebayes

