//
// Created by pbarbeira on 02-03-2025.
//

#ifndef PROCESSINGUNIT_H
#define PROCESSINGUNIT_H

#include <memory>
#include <functional>
#include <utility>
#include "../tree-loader/Instance.h"
#include "../tree-loader/Node.h"

using ull = unsigned long long;

template<typename T>
class ProcessingUnit;

enum PEDirection{
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

template<typename T>
class ProcessingUnit {
        ull _id = -1;
        std::shared_ptr<CycleCounter> _cycleCounter;
        std::shared_ptr<ProcessingUnit<T>> _neighbors[4];

        std::function<int(const Instance<T>&)> _functionalUnit;
    public:
        explicit ProcessingUnit() = default;

        explicit ProcessingUnit(std::shared_ptr<CycleCounter> cycleCounter):
            _cycleCounter(std::move(cycleCounter)){};

        void activate(std::unique_ptr<Node<T>> node){
            this->_id = node->id;

            auto data = node->getData();

            if(data.first == LEAF_ATTRIBUTE){
                this->_functionalUnit = [data](const Instance<T>& instance) -> int {
                    return data.second;
                };
                return;
            };

            this->_neighbors[LEFT] = std::make_unique<ProcessingUnit<T>>(this->_cycleCounter);
            this->_neighbors[LEFT]->activate(std::move(node->left));
            this->_neighbors[RIGHT] = std::make_unique<ProcessingUnit<T>>(this->_cycleCounter);
            this->_neighbors[RIGHT]->activate(std::move(node->right));

            this->_functionalUnit = [this, data](const Instance<T>& instance) -> int {
                T value = instance.features[data.first];
                return value < data.second ?
                    this->_neighbors[LEFT]->classify(instance) :
                    this->_neighbors[RIGHT]->classify(instance);
            };
        }

        bool setNeighbor(PEDirection direction, std::shared_ptr<ProcessingUnit<T>> neighbor){
            if(this->_neighbors[direction] == nullptr){
                this->_neighbors[direction] = neighbor;
                return true;
            }
            return false;
        }

        int classify(const Instance<T>& instance){
            this->_cycleCounter->count("infer");
            return this->_functionalUnit(instance);
        }
};



#endif //PROCESSINGUNIT_H
