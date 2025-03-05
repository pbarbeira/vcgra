//
// Created by pbarbeira on 02-03-2025.
//

#ifndef NODE_H
#define NODE_H

#include <memory>
#include <utility>

#define LEAF_ATTRIBUTE -1

using ull = unsigned long long;

template<typename T>
struct Node;

template<typename T>
struct Node {
      std::unique_ptr<Node<T>> left;
      std::unique_ptr<Node<T>> right;

      virtual std::pair<T, T> getData() const = 0;
};

template<typename T>
struct SplitNode : public Node<T> {
      T splitAttribute;
      T splitValue;

      std::pair<T, T> getData() const {
        return std::make_pair<T, T>(splitAttribute, splitValue); 
      }
};

template<typename T>
struct LeafNode : public Node<T> {
      T value;

      std::pair<T, T> getData() const {
        return std::make_pair<T, T>(LEAF_ATTRIBUTE, value); 
      }
};

#endif //NODE_H
