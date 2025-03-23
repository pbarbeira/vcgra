//
// Created by pbarbeira on 11-03-2025.
//

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include "JsonNode.h"
#include "Lexer.h"

class JsonParser {
        static std::unique_ptr<JsonNode> _parseObject(){
            auto objRoot = std::make_unique<JsonNode>();
            do{
                std::string key = _parseKey();
                auto value = _parseValue();
                if(!objRoot->addChild(key, std::move(value))){
                    throw std::runtime_error("Duplicate key error");
                }
                auto token = Lexer::nextToken();
                if (token->type == RIGHT_CURLY) {
                    break;
                }
                if (token->type != COMMA) {
                    throw std::runtime_error("Invalid separator");
                }
            }while(Lexer::hasNextToken() && Lexer::peekNextToken()->type != RIGHT_CURLY);
            return std::move(objRoot);
        }

        static std::string _parseKey(){
            auto token = Lexer::nextToken();
            std::string key = token->value;
            token = Lexer::nextToken();
            if(token->type != COLON){
                throw std::runtime_error("Error parsing key");
            }
            return key;
        }

        static std::unique_ptr<JsonNode> _parseValue(){
            auto token = Lexer::nextToken();
            switch(token->type){
                case LEFT_CURLY: return _parseObject();
                case LEFT_SQUARE: return _parseList();
                case STRING:
                case NUMBER:
                case TRUE:
                case FALSE:
                case NIL: return std::make_unique<JsonNode>(token->value);
                default: throw std::runtime_error("Error parsing value");
            }
        }

        static std::unique_ptr<JsonNode> _parseList(){
            auto objRoot = std::make_unique<JsonNode>();
            do {
                auto item = _parseValue();
                objRoot->addChild("", std::move(item));
                auto token = Lexer::nextToken();
                if (token->type == RIGHT_SQUARE) {
                    break;
                }
                if (token->type != COMMA) {
                    throw std::runtime_error("Invalid separator");
                }
            }while (Lexer::hasNextToken() && Lexer::peekNextToken()->type != RIGHT_SQUARE);
            return std::move(objRoot);
        }

    public:
        JsonParser();

        template<typename T>
        static T parse(const std::string& input){
            Lexer::registerInput(input);
            auto token = Lexer::nextToken();
            if(token->type != LEFT_CURLY){
                throw std::runtime_error("Invalid object structure");
            }
            return _parseObject()->toObject<T>();
        }
};

#endif //JSONPARSER_H
