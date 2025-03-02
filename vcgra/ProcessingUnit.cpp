//
// Created by pbarbeira on 02-03-2025.
//

#include "ProcessingUnit.h"

bool ProcessingUnit::setNeighbor(PEDirection direction, std::shared_ptr<ProcessingUnit> neighbor){
    if(this->_neighbors[direction] == nullptr){
        this->_neighbors[direction] = neighbor;
        return true;
    }
    return false;
}

int ProcessingUnit::classify(const Instance& instance){
    return this->_functionalUnit(instance);
}