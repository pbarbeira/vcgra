//
// Created by pbarbeira on 02-03-2025.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

#define TRAINING_INSTANCE (-1)

template<typename T>
struct Instance {
  short classId;
  std::vector<T> features;

  Instance():
    classId(TRAINING_INSTANCE){}

  explicit Instance(std::vector<T> features):
    classId(TRAINING_INSTANCE), features(features){}

  explicit Instance(short classId):
    classId(classId){}


  Instance(short classId, std::vector<T> features):
      classId(classId), features(features){};

  [[nodiscard]] bool isTrainingInstance() const {
    return classId == TRAINING_INSTANCE;
  }
};

#endif //INSTANCE_H
