//
// Created by pbarbeira on 02-03-2025.
//

#ifndef NODE_H
#define NODE_H

#include "../vcgra/ProcessingUnit.h"
#include <memory>

class Node;

struct Node {
      std::unique_ptr<Node> left;
      std::unique_ptr<Node> right;

      virtual std::shared_ptr<ProcessingUnit> BuildProcessingUnit() = 0;
};

struct SplitNode : public Node {
      int splitAttribute;
      int splitValue;

      std::shared_ptr<ProcessingUnit> BuildProcessingUnit() override;
};

struct LeafNode : public Node {
      int value;

      std::shared_ptr<ProcessingUnit> BuildProcessingUnit() override;
};



#endif //NODE_H
