//
// Created by pbarbeira on 21-03-2025.
//

#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

class JsonNode{
        std::vector<std::unique_ptr<JsonNode>> _children;

        std::vector<std::unique_ptr<JsonNode>>::iterator _findKey(const std::string& key){
            return std::ranges::find_if(_children, [key](const std::unique_ptr<JsonNode>& child){
                    return child->key == key;
                });
        }

    public:
        std::string value;
        std::string key;

        JsonNode(){}

        JsonNode(const std::string& value):
            value(value){}

        bool addChild(const std::string& key, std::unique_ptr<JsonNode> child){
            if (!key.empty()) {
                std::string cleanKey = key.substr(1, key.size() - 2);
                if(_findKey(cleanKey) != _children.end()){
                    return false;
                }
                child->key = cleanKey;
            }
            _children.emplace_back(std::move(child));
            return true;
        }

        JsonNode* getChild(const std::string& key){
            auto found = _findKey(key);
            if(found != _children.end()){
                return found->get();
            }
            return nullptr;
        }

        template<typename T>
        T toObject(){
            throw "No viable conversion for type\n";
        }
};

#endif //JSONNODE_H
