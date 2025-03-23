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
            return std::move(JsonParser::parse<std::unique_ptr<MappingConfig>>(ss.str()));
        }
};

template<>
inline std::unique_ptr<NodeMapping> JsonNode::toObject<std::unique_ptr<NodeMapping>>(){
    std::string xPosStr = this->getChild("xPos")->value;
    std::string yPosStr = this->getChild("yPos")->value;

    auto nodeMapping = std::make_unique<NodeMapping>();
    nodeMapping->xPos = std::stoi(xPosStr);
    nodeMapping->yPos = std::stoi(yPosStr);

    return std::move(nodeMapping);
}

template<>
inline std::unique_ptr<MappingConfig> JsonNode::toObject<std::unique_ptr<MappingConfig>>(){
    auto config = std::make_unique<MappingConfig>();

    auto gridNPtr = this->getChild("N");
    config->N = std::stoi(gridNPtr->value);

    auto gridMPtr = this->getChild("M");
    config->M = std::stoi(gridMPtr->value);

    auto nodes = this->getChild("nodes");
    for (const auto& node : nodes->_children) {
        std::string keyStr = node->key;
        ull key = keyStr == "entryNode"? ENTRY_NODE : std::stoull(node->key);
        auto nodeMapping = node->toObject<std::unique_ptr<NodeMapping>>();
        config->_nodeMap[key] = std::move(nodeMapping);
    }

    return std::move(config);
}



#endif //MAPPINGCONFIG_H
