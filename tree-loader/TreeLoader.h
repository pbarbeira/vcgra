//
// Created by pbarbeira on 02-03-2025.
//

#ifndef TREELOADER_H
#define TREELOADER_H

#include "Node.h"

template<typename T>
class TreeLoader {
    public:
      virtual Node<T> loadTree(std::string filepath) = 0;
};

template<typename T>
class DotTreeLoader : TreeLoader<T>{
    public:
        Node<T> loadTree(std::string filepath) override;
};



#endif //TREELOADER_H
