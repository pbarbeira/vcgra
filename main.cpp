#include <iostream>
#include "vcgra/CycleCounter.h"
#include <vector>
#include "tree-loader/Node.h"
#include "tree-loader/TreeLoader.h"
#include "vcgra/ProcessingUnit.h"

int main() {
    auto loader = DotTreeLoader<int>();
    auto root = loader.loadTree("/home/pbarbeira/masters/dissertation/vcgra/trees/tree.dot");

    if (root == nullptr) {
        std::cerr << "Failed to load tree" << std::endl;
        return 1;
    }

    auto cycleCounter = std::make_shared<CycleCounter>();

    auto pe = ProcessingUnit<int>(cycleCounter);
    pe.activate(std::move(root));

    std::vector<int> v1 = { 1, 2, 3, 4 };
    std::vector<int> v2 = { 1, 3, 3, 4 };
    std::vector<int> v3 = { 5, 2, 3, 4 };

    auto inst1 = Instance(v1);
    auto inst2 = Instance(v2);
    auto inst3 = Instance(v3);

    auto r1 = pe.classify(inst1);
    auto c1 = cycleCounter->getCycles();
    cycleCounter->reset();
    auto r2 = pe.classify(inst2);
    auto c2 = cycleCounter->getCycles();
    cycleCounter->reset();
    auto r3 = pe.classify(inst3);
    auto c3 = cycleCounter->getCycles();
    cycleCounter->reset();

    std::cout << "V1: " << r1 << "\tCycles: " << c1
            << "\nV2: " << r2 << "\tCycles: " << c2
            << "\nV3: " << r3 << "\tCycles: " << c3
            << std::endl;

    return 0;
}
