//
// Created by pbarbeira on 02-03-2025.
//

#ifndef TREELOADER_H
#define TREELOADER_H

#include "Node.h"

class TreeLoader {
    public:
      std::unique_ptr<Node> loadTree(std::string treeStr);
};



#endif //TREELOADER_H
