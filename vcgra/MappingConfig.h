//
// Created by pbarbeira on 10-03-2025.
//

#ifndef MAPPINGCONFIG_H
#define MAPPINGCONFIG_H

#include <unordered_map>
#include <memory>
#include "../json-parse/JsonParser.h"

using ull = unsigned long long;
using uint = unsigned int;

#define ENTRY_NODE 0

struct NodeMapping{
    uint xPos;
    uint yPos;
};

struct MappingConfig {
        uint N{};
		uint M{};
        std::unordered_map<ull, std::unique_ptr<NodeMapping>> _nodeMap;

        static std::unique_ptr<MappingConfig> loadFromFile(const std::string& filename) {
            std::stringstream ss;
            std::ifstream file(filename);
            std::string line;
            while(std::getline(file, line)){
                ss << line;
            }
            return std::move(JsonParser::parseJson<std::unique_ptr<MappingConfig>>(ss.str()));
        }
};

template<>
inline std::unique_ptr<NodeMapping> JsonObject::toObject<std::unique_ptr<NodeMapping>>() const{
    std::string xPosStr = this->getChild("xPos")->_value;
    std::string yPosStr = this->getChild("yPos")->_value;

    auto nodeMapping = std::make_unique<NodeMapping>();
    nodeMapping->xPos = std::stoi(xPosStr);
    nodeMapping->yPos = std::stoi(yPosStr);

    return std::move(nodeMapping);
}

template<>
inline std::unique_ptr<MappingConfig> JsonObject::toObject<std::unique_ptr<MappingConfig>>() const{
    auto config = std::make_unique<MappingConfig>();

    auto gridNPtr = this->getChild("N");
    config->N = std::stoi(gridNPtr->_value);

    auto gridMPtr = this->getChild("M");
    config->M = std::stoi(gridMPtr->_value);

    auto nodes = this->getChild("nodes");
    for (const auto& node : nodes->_children) {
        std::string keyStr = node.first;
        ull key = keyStr == "entryNode"? ENTRY_NODE : std::stoull(node.first);
        auto nodeMapping = node.second->toObject<std::unique_ptr<NodeMapping>>();
        config->_nodeMap[key] = std::move(nodeMapping);
    }

    return std::move(config);
}



#endif //MAPPINGCONFIG_H
