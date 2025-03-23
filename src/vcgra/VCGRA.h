//
// Created by pbarbeira on 02-03-2025.
//

#ifndef VCGRA_H
#define VCGRA_H

#include "../tree-loader/TreeLoader.h"
#include "CycleCounter.h"
#include <unordered_map>
#include "ProcessingUnit.h"
#include "VCGRAConfig.h"

using ull = unsigned long long;

template<typename T>
class VCGRA {
		std::unique_ptr<VCGRAConfig> _config;
		std::unique_ptr<TreeLoader<T>> _loader;
		std::shared_ptr<ProcessingUnit<T>> _entryNode;
		std::vector<std::shared_ptr<ProcessingUnit<T>>> _processingUnits;

		std::shared_ptr<ProcessingUnit<T>> _getProcessingUnit(const ull& id){
			try {
				int index = _calculateIndex(id);
				return _processingUnits[index];
			}catch (std::exception e) {
				std::cerr << e.what();
			}
			return nullptr;
		}

		int _calculateIndex(ull id) {
			if (!this->_config->nodeMap.contains(id)) {
				throw std::runtime_error(std::format("VCGRA: Node [{}] not found", id));
			}
			auto nodeMapping = this->_config->nodeMap.at(id).get();
			return nodeMapping->xPos + nodeMapping->yPos * this->_config->M;
		}

		void _initProcessingUnits(const std::shared_ptr<CycleCounter>& cycleCounter) {
			if (this->_config->N == 0 || this->_config->M == 0) {
				throw std::runtime_error(std::format("VCGRA: No processing units found"));
			}
			for (int i = 0; i < this->_config->N * this->_config->M; i++) {
				_processingUnits.push_back(std::make_shared<ProcessingUnit<T>>(cycleCounter));
			}
			int entryPos = _calculateIndex(ENTRY_NODE);
			this->_entryNode = _processingUnits[entryPos];
		}
    public:
		VCGRA(std::unique_ptr<VCGRAConfig> config, std::unique_ptr<TreeLoader<T>> loader, const std::shared_ptr<CycleCounter> &cycleCounter):
            _config(std::move(config)), _loader(std::move(loader)) {
			_initProcessingUnits(cycleCounter);
		}
            
		void loadHoeffdingTree(const std::string& filepath){
            auto root = _loader->loadTree(filepath);
			if(_entryNode == nullptr) {
				throw std::runtime_error("Could not load entry node");
			}
			auto callback = [this](const ull& id){ return this->_getProcessingUnit(id); };
			_entryNode->activate(std::move(root), callback);
		}

		int classify(const Instance<T>& instance) {
			return _entryNode->classify(instance);
		}
};



#endif //VCGRA_H
