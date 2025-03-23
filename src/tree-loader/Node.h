//
// Created by pbarbeira on 02-03-2025.
//

#ifndef NODE_H
#define NODE_H

#include <memory>
#include <utility>

#define LEAF_ATTRIBUTE (-1)

using ull = unsigned long long;

template<typename T>
struct Node;

template<typename T>
struct Node {
    ull id{};

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const ull id):
        id(id){};

    [[nodiscard]] virtual std::pair<int, T> getData() const = 0;

    virtual ~Node() = default;
};

template<typename T>
struct SplitNode final : Node<T> {
    int splitAttribute;
    T splitValue;

    explicit SplitNode(const ull id, int splitAttribute, T splitValue):
        Node<T>(id), splitAttribute(splitAttribute), splitValue(splitValue){};

    std::pair<int, T> getData() const override {
        return std::make_pair(splitAttribute, splitValue);
    }
};

template<typename T>
struct LeafNode final : Node<T> {
    int classId;

    explicit LeafNode(const ull id, const int classId):
        Node<T>(id), classId(classId){};

    [[nodiscard]] std::pair<int, T> getData() const override {
        return std::make_pair(LEAF_ATTRIBUTE, classId);
    }
};

#endif //NODE_H
