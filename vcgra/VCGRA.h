//
// Created by pbarbeira on 02-03-2025.
//

#ifndef VCGRA_H
#define VCGRA_H

#include "../tree-loader/TreeLoader.h"
#include <unordered_map>
#include "ProcessingUnit.h"

using ull = unsigned long long;

template<typename T>
class VCGRA {
    private:
      	int size;
        // TODO implement manual version of spatial mapping
		std::unordered_map<ull, std::shared_ptr<ProcessingUnit<T>>> processingUnits;
    public:
		VCGRA() : size(0) {};
            
		void loadTree(const Node<T>& root);
};



#endif //VCGRA_H
