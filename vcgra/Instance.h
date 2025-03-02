//
// Created by pbarbeira on 02-03-2025.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

#define TRAINING_INSTANCE -1

struct Instance {
  short class_id;

  Instance():
    class_id(TRAINING_INSTANCE){}

  Instance(short class_id):
    class_id(class_id){}

  bool isTrainingInstance() const {
    return class_id == TRAINING_INSTANCE;
  }
};

struct IntInstance : public Instance {
  std::vector<int> features;

  IntInstance(std::vector<int> features):
    Instance(), features(features){}

  IntInstance(short class_id, std::vector<int> features):
    Instance(class_id), features(features){}
};

struct DoubleInstance : public Instance {
  std::vector<double> features;

  DoubleInstance(std::vector<double> features):
    Instance(), features(features){}

  DoubleInstance(short class_id, std::vector<double> features):
    Instance(class_id), features(features){}
};


#endif //INSTANCE_H
