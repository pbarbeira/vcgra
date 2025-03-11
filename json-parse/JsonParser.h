//
// Created by pbarbeira on 11-03-2025.
//

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "JsonObject.h"
#include <iostream>
#include <string>
#include <stack>
#include <sstream>

class JsonParser{
    private:
        static std::string _removeWhitespace(const std::string& s){
            std::stringstream ss;
            for(int i = 0; i < s.size(); i++){
                if(!std::isspace(s[i])){
                    ss << s[i];
                }
            }
            return ss.str();
        }

        static std::unique_ptr<JsonObject> _parseKeyValue(const std::string& jsonStr){
            if (jsonStr[0] == '{') {
                auto jsonObj = std::make_unique<JsonObject>("");
                return _parseObject(jsonStr.substr(1, jsonStr.size() - 1), std::move(jsonObj));
            }
            return std::make_unique<JsonObject>(jsonStr);
        }

        static std::unique_ptr<JsonObject> _parseObject(const std::string& jsonStr, std::unique_ptr<JsonObject> parent){
            std::stack<std::string> stack;
            std::stack<char> bracketStack;
            int last = 0;
            for(int i = 0; i < jsonStr.size(); i++){
                if(jsonStr[i] == '{') {
                    while (1) {
                        if (jsonStr[i] == '{') {
                            bracketStack.emplace(jsonStr[i]);
                        }
                        if (jsonStr[i] == '}') {
                            bracketStack.pop();
                        }
                        if (bracketStack.empty()) {
                            break;
                        }
                        i++;
                    }
                }
                if(jsonStr[i] == ':'){
                    std::string key = jsonStr.substr(last, i - last);
                    stack.emplace(key);
                    stack.emplace(":");
                    last = i + 1;
                }
                if(jsonStr[i] == ',' || i == jsonStr.size() - 1){
                    stack.pop();
                    std::string key = stack.top();
                    key = key.substr(1, key.size() - 2);
                    stack.pop();
                    std::string value = jsonStr.substr(last, i == jsonStr.size() - 1 ? i - last + 1 : i - last);
                    auto jsonObj = _parseKeyValue(value);
                    parent->addChild(key, std::move(jsonObj));
                    last = i + 1;
                }
            }
            return std::move(parent);
        }

    public:
    template<typename T>
    static T parseJson(const std::string& jsonStr){
        try{
            auto root = std::make_unique<JsonObject>("");
            auto cleanStr = _removeWhitespace(jsonStr);
            return _parseObject(cleanStr.substr(1, cleanStr.size() - 2), std::move(root))->toObject<T>();
        }catch(const std::exception& e){
            std::cerr << "FATAL::" << e.what() << std::endl;
            exit(1);
        }
    }
};

#endif //JSONPARSER_H
