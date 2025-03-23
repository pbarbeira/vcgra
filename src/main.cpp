#include <iostream>
#include "vcgra/CycleCounter.h"
#include <vector>
#include "tree-loader/Node.h"
#include "tree-loader/TreeLoader.h"
#include "vcgra/ProcessingUnit.h"
#include "json-parse/JsonParser.h"
#include "vcgra/VCGRA.h"
#include "vcgra/VCGRAConfig.h"

#define VCGRA_CONFIG "/home/pbarbeira/masters/dissertation/vcgra/config/vcgra-config.json"
#define CYCLE_CONFIG "/home/pbarbeira/masters/dissertation/vcgra/config/cycle-config.json"
#define TREE_CONFIG "/home/pbarbeira/masters/dissertation/vcgra/trees/tree.dot"

int main() {

    auto vcgraConfig = VCGRAConfig::loadFromFile(VCGRA_CONFIG);
    std::unique_ptr<TreeLoader<int>> loader = std::make_unique<DotTreeLoader<int>>();
    auto cycleCounter = std::make_shared<CycleCounter>(CYCLE_CONFIG);

    auto vcgra = VCGRA(std::move(vcgraConfig), std::move(loader), std::move(cycleCounter));

    vcgra.loadHoeffdingTree(TREE_CONFIG);

    std::vector v1 = { 1, 2, 3, 4 };
    std::vector v2 = { 1, 3, 3, 4 };
    std::vector v3 = { 5, 2, 3, 4 };

    auto inst1 = Instance(v1);
    auto inst2 = Instance(v2);
    auto inst3 = Instance(v3);

    std::cout << "Instace 1 - Class: " << vcgra.classify(inst1) << '\n'
            << "Instace 2 - Class: " << vcgra.classify(inst2) << '\n'
            << "Instace 3 - Class: " << vcgra.classify(inst3) << '\n'
            << std::endl;

    return 0;
}
