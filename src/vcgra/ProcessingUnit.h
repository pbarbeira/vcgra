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

template<typename T>
class ProcessingUnit {
        ull _id = -1;
        std::weak_ptr<CycleCounter> _cycleCounter;
        std::shared_ptr<ProcessingUnit> _left;
        std::shared_ptr<ProcessingUnit> _right;

        std::function<int(const Instance<T>&)> _functionalUnit;
    public:
        explicit ProcessingUnit() = default;

        explicit ProcessingUnit(const std::shared_ptr<CycleCounter>& cycleCounter):
            _cycleCounter(cycleCounter){};

        void activate(std::unique_ptr<Node<T>> node, std::function<std::shared_ptr<ProcessingUnit>(const ull&)> callback){
            this->_id = node->id;

            auto data = node->getData();

            if(data.first == LEAF_ATTRIBUTE){
                this->_functionalUnit = [data](const Instance<T>&) -> int {
                    return data.second;
                };
                return;
            };

            this->_left = callback(node->left->id);
            this->_left->activate(std::move(node->left), callback);

            this->_right = callback(node->right->id);;
            this->_right->activate(std::move(node->right), callback);

            this->_functionalUnit = [this, data](const Instance<T>& instance) -> int {
                T value = instance.features[data.first];
                return value < data.second ?
                    this->_left->classify(instance) :
                    this->_right->classify(instance);
            };
        }

        int classify(const Instance<T>& instance){
            if (auto p = this->_cycleCounter.lock()) {
                p->count("infer");
                return this->_functionalUnit(instance);
            }
            throw std::logic_error("Cycle counter expired");
        }
};



#endif //PROCESSINGUNIT_H
