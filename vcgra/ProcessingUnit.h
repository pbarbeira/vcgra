//
// Created by pbarbeira on 02-03-2025.
//

#ifndef PROCESSINGUNIT_H
#define PROCESSINGUNIT_H

#include <memory>
#include <functional>
#include "Instance.h"
#include "../tree-loader/Node.h"

using ull = unsigned long long;

template<typename T>
class ProcessingUnit;

enum PEDirection{
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

template<typename T>
class ProcessingUnit {
    private:
        ull _id;
        std::shared_ptr<ProcessingUnit<T>> _neighbors[4];

        std::function<int(const Instance<T>&)> _functionalUnit;
    public:
        explicit ProcessingUnit(){} 
        
        void activate(const Node<T>& node);        

        bool setNeighbor(PEDirection direction, std::shared_ptr<ProcessingUnit<T>> neighbor);

        int classify(const Instance<T>& instance);
};



#endif //PROCESSINGUNIT_H
