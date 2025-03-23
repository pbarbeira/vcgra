#ifndef CYCLE_COUNTER_H_
#define CYCLE_COUNTER_H_

#include <unordered_map>
#include <fstream>
#include <sstream>

#include "../json-parse/JsonParser.h"

using ull = unsigned long long;

class CycleCounter{
        ull _totalCycles;
        std::unordered_map<std::string, int> _opCycles;

    public:
        explicit CycleCounter(std::string configPath){
            _totalCycles = 0;
            std::stringstream ss;
            std::ifstream file(configPath);
            std::string line;
            while(std::getline(file, line)){
                ss << line;
            }
            _opCycles = JsonParser::parse<std::unordered_map<std::string, int>>(ss.str());
        }

        void count(const std::string& op){
            if(_opCycles.contains(op)){
                _totalCycles += _opCycles[op];
            }
        }

        ull getCycles() const{
            return _totalCycles;
        }

        void reset() {
            _totalCycles = 0;
        }
};

template<>
inline std::unordered_map<std::string, int> JsonNode::toObject<std::unordered_map<std::string, int>>(){
    std::unordered_map<std::string, int> result;
    std::ranges::for_each(this->_children, [&](auto& child) {
        result[child->key] = std::stoi(child->value);
    });

    return result;
}

#endif //CYCLE_COUNTER_H_
