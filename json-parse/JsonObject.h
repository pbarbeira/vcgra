//
// Created by pbarbeira on 11-03-2025.
//

#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <unordered_map>
#include <format>
#include <memory>

class JsonObject;

class JsonObject{
    private:
        std::string _value;
        std::unordered_map<std::string, std::unique_ptr<JsonObject>> _children;
    public:
        explicit JsonObject(const std::string& value):
             _value(value){
          this->_children.clear();
        }

        template<typename T>
        T toObject() const{
            throw "No viable conversion for type\n";
        }

        JsonObject* getChild(const std::string& key) const{
            if(this->_children.contains(key)){
                return this->_children.at(key).get();
            }
            return nullptr;
        }

        void addChild(const std::string& key, std::unique_ptr<JsonObject> child){
            if(this->_children.contains(key)){
                throw std::format("Key '{}' already exists.", key);
            }
            this->_children[key] = std::move(child);
        }
};



#endif //JSONOBJECT_H
