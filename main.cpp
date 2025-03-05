#include <iostream>
#include "vcgra/CycleCounter.h"
#include <vector>
#include "tree-loader/Node.h"
#include "vcgra/ProcessingUnit.h"

int main() {
    auto root = sd::make_unique<SplitNode<int>>();
    root->splitAttribute = 0;
    root->splitValue = 5;

    auto left = std::make_unique<SplitNode<int>>();
    left->splitAttribute = 1; 
    left->splitValue = 3;

    auto leaf1 = std::make_unique<LeafNode<int>>();
    leaf1->value = 1;
    auto leaf2 = std::make_unique<LeafNode<int>>();
    leaf2->value = 2;
    auto leaf3 = std::make_unique<LeafNode<int>>();
    leaf3->value = 3;

    left->left = leaf1;
    left->right = leaf2;
    root->left = left;
    root->right = leaf3;

    auto pe = ProcessingUnit<int>();
    pe.activate(root);

    std::vector<int> v1 = { 1, 2, 3, 4 };
    std::vector<int> v2 = { 1, 3, 3, 4 };
    std::vector<int> v3 = { 5, 2, 3, 4 };

    auto inst1 = Instance(v1);
    auto inst2 = Instance(v2);
    auto inst3 = Instance(v3);

    std::cout << "V1: " << pe.classify(v1)  
            << "\nV2: " << pe.classify(v2) 
            << "\nV3: " << pe.classify(v3) << std::endl;

    return 0;
}
