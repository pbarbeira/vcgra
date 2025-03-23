//
// Created by pbarbeira on 02-03-2025.
//

#ifndef VCGRA_H
#define VCGRA_H

#include "../tree-loader/TreeLoader.h"
#include <unordered_map>
#include "ProcessingUnit.h"
#include "MappingConfig.h"

#define CONFIG_FILE "/home/pbarbeira/masters/dissertation/vcgra/node-mapping.json"

using ull = unsigned long long;

template<typename T>
class VCGRA {
    private:
        std::unique_ptr<MappingConfig> _config;
		std::unordered_map<ull, std::shared_ptr<ProcessingUnit<T>>> _processingUnits;

		std::weak_ptr<ProcessingUnit<T>> getProcessingUnit(ull id){
			if(this->_processingUnits.contains(id)){
				return this->_processingUnits.at(id);
			}
			return nullptr;
		}
    public:
		VCGRA(){
            _config = std::move(MappingConfig::loadFromFile(CONFIG_FILE));
		};
            
		static VCGRA buildHoeffdingTree(){
			                  
		}
};



#endif //VCGRA_H
