//
// Created by pbarbeira on 02-03-2025.
//

#ifndef PROCESSINGUNIT_H
#define PROCESSINGUNIT_H

#include <memory>
#include <functional>
#include "Instance.h"

using ull = unsigned long long;

class ProcessingUnit;

enum PEDirection{
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

class ProcessingUnit {
    private:
        ull _id;
        std::shared_ptr<ProcessingUnit> _neighbors[4];

        std::function<int(const Instance&)> _functionalUnit;
    public:
        explicit ProcessingUnit();

        template<typename T>
        explicit ProcessingUnit(ull id, std::function<int(Instance)> functionalUnit)
            :_id(id), _functionalUnit(functionalUnit) {};

        bool setNeighbor(PEDirection direction, std::shared_ptr<ProcessingUnit> neighbor);

        int classify(const Instance& instance);
};



#endif //PROCESSINGUNIT_H
