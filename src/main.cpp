#include <iostream>
#include "vcgra/CycleCounter.h"
#include <vector>
#include "tree-loader/Node.h"
#include "tree-loader/TreeLoader.h"
#include "vcgra/ProcessingUnit.h"
#include "json-parse/JsonParser.h"
#include "vcgra/VCGRA.h"
#include "vcgra/VCGRAConfig.h"

#define VCGRA_CONFIG ""
#define CYCLE_CONFIG ""
#define TREE_CONFIG ""

int main() {

    auto vcgraConfig = VCGRAConfig::loadFromFile(VCGRA_CONFIG);
    std::unique_ptr<TreeLoader<int>> loader = std::make_unique<DotTreeLoader<int>>();
    auto cycleCounter = std::make_shared<CycleCounter>();

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
