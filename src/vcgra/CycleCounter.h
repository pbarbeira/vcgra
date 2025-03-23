#ifndef CYCLE_COUNTER_H_
#define CYCLE_COUNTER_H_

#include <unordered_map>

using ull = unsigned long long;

class CycleCounter{
        ull _totalCycles;
        std::unordered_map<std::string, int> _opCycles = {
            { "infer", 1 },
            { "add", 5 },
            // make this in accordance with physical cgra
        };
    public:
        explicit CycleCounter(){
            _totalCycles = 0;
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

#endif //CYCLE_COUNTER_H_
