#ifndef CYCLE_COUNTER_H_
#define CYCLE_COUNTER_H_

#include <unordered_map>

using ull = unsigned long long;

class CycleCounter{
    private:
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

        void count(std::string op){
            if(_opCycles.find(op) != _opCycles.end()){
                _totalCycles += _opCycles[op];
            }
        }

        ull getCycles() const{
            return _totalCycles;
        }
};

#endif //CYCLE_COUNTER_H_
