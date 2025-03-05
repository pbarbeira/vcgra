//
// Created by pbarbeira on 02-03-2025.
//

#include "ProcessingUnit.h"

template<typename T>
void ProcessingUnit<T>::activate(const Node<T>& node){
    this->_id = node->id;

    auto data = node->getData();
   
    if(data->first == LEAF_ATTRIBUTE){
        this->_functionalUnit = [data](const Instance<T>& instance) -> int {
            return data->second;
        };
        return;
    };
    
    this->left = std::make_unique<ProcessingUnit<T>>();
    this->left->activate(node->left);
    this->right = std::make_unique<ProcessingUnit<T>>();
    this->right->activate(node->right);

    this->_functionalUnit = [this, data](const Instance<T>& instance) -> int {
        T value = instance.features[data->first];
        return value < data->second ?
            this->_neighbors[LEFT]->classify(instance) :
            this->_neighbors[RIGHT]->classify(instance);
    };
}

template<typename T>
bool ProcessingUnit<T>::setNeighbor(PEDirection direction, std::shared_ptr<ProcessingUnit> neighbor){
    if(this->_neighbors[direction] == nullptr){
        this->_neighbors[direction] = neighbor;
        return true;
    }
    return false;
}

template<typename T>
int ProcessingUnit<T>::classify(const Instance<T>& instance){
    return this->_functionalUnit(instance);
}
