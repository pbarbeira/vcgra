//
// Created by pbarbeira on 02-03-2025.
//

#ifndef VCGRA_H
#define VCGRA_H

#include "../tree-loader/TreeLoader.h"
#include <unordered_map>

class VCGRA {
    private:
      	int size;
		std::unordered_map<int, std::shared_ptr<ProcessingUnit>> processingUnits;

		bool addProcessingUnit(std::shared_ptr<ProcessingUnit> unit);
    public:
		VCGRA() : size(0) {};

		void loadTree(std::unique_ptr<Node> root);
};



#endif //VCGRA_H
