//
// Created by pbarbeira on 08-03-2025.
//

#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include <iostream>

class TypeConverter {
public:
    template<typename T>
    static T convert(const std::string& value) {
        throw "No viable conversion for type\n";
    }
};

template<>
inline int TypeConverter::convert<int>(const std::string& value) {
    return std::stoi(value);
}

template<>
inline double TypeConverter::convert<double>(const std::string& value) {
    return std::stod(value);
}

template<>
inline float TypeConverter::convert<float>(const std::string& value) {
    return std::stof(value);
}

#endif //TYPECONVERTER_H
