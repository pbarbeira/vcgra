//
// Created by pbarbeira on 02-03-2025.
//

#ifndef TREELOADER_H
#define TREELOADER_H

#include "Node.h"
#include <unordered_map>
#include <fstream>
#include <regex>
#include "TypeConverter.h"
#include <format>

using ull = unsigned long long;

template<typename T>
class TreeLoader {
	protected:
		std::unordered_map<ull, Node<T>*> _nodes;
		std::unique_ptr<Node<T>> _root = nullptr;
	public:
		virtual std::unique_ptr<Node<T>> loadTree(const std::string& filepath) = 0 ;

		virtual ~TreeLoader() {
			_nodes.clear();
		}
};

template<typename T>
class DotTreeLoader : public TreeLoader<T>{
  	std::regex _nodePattern = std::regex(R"(\s*(\d+) \[label=\"(.*?)\"\];)");
	std::regex _splitNodePattern = std::regex(R"(Feature\[(\d+)\] < (\d+\.?\d+))");
	std::regex _leafNodePattern = std::regex(R"(ClassId=(\d+))");
	std::regex _edgePattern = std::regex(R"(\s*(\d+) -> \{ (\d+) (\d+) \};)");

  	void parseNodeDefinition(const std::smatch& input){
  		ull id = std::stoull(input[1].str());
  		std::smatch match;
  		std::string contentStr = input[2].str();
		Node<T>* node = nullptr;
  		if (std::regex_match(contentStr, match, _splitNodePattern)) {
  			int splitAttribute = std::stoi(match[1].str());
  			T splitValue = TypeConverter::convert<T>(match[2].str());
  			node = new SplitNode<T>(id, splitAttribute, splitValue);
  		}
	    if (std::regex_match(contentStr, match, _leafNodePattern)) {
	    	int classId = std::stoi(match[1].str());
	    	node = new LeafNode<T>(id, classId);
  		}
		this->_nodes[node->id] = node;

  		if (this->_root == nullptr) {
  			this->_root = std::unique_ptr<Node<T>>(node);
  		}
    }

    void parseEdgeDefinition(const std::smatch& input){
  		int nodeId = std::stoi(input[1].str());
  		if (!this->_nodes.contains(nodeId)) {
  			throw std::invalid_argument(std::format("Node [{}] does not exist", nodeId));
  		}
  		auto node = this->_nodes[nodeId];

  		int leftId = std::stoi(input[2].str());
  		if (!this->_nodes.contains(leftId)) {
  			throw std::invalid_argument(std::format("Node [{}] does not exist", leftId));
  		}
  		auto left = this->_nodes[leftId];

  		int rightId = std::stoi(input[3].str());
  		if (!this->_nodes.contains(rightId)) {
  			throw std::invalid_argument(std::format("Node [{}] does not exist", rightId));
  		}
  		auto right = this->_nodes[rightId];

  		node->left = std::unique_ptr<Node<T>>(left);
  		node->right = std::unique_ptr<Node<T>>(right);
    }

	public:
		DotTreeLoader(): TreeLoader<T>(){}

        std::unique_ptr<Node<T>> loadTree(const std::string& filepath) override {
	        std::ifstream file(filepath);
	        try {
		        std::string input;
		        int lineCount = 0;
        		while(std::getline(file, input)) {
        			lineCount++;
					if (input.empty()) {
						continue;
					}
        			std::smatch match;
        			if(std::regex_match(input, match, _nodePattern)) {
        				parseNodeDefinition(match);
        			}
        			else if(std::regex_match(input, match, _edgePattern)) {
        				parseEdgeDefinition(match);
        			}
        			if (!match[0].matched && lineCount != 1 && input != "}") {
        				std::cerr << std::format("Incorrect format at line {}\n", lineCount);
        				return nullptr;
        			}
        		}
        	}catch (const std::exception& ex) {
        		std::cerr << "[FATAL]::" << ex.what() << '\n';
        		return nullptr;
        	}
        	return std::move(this->_root);
        }
};



#endif //TREELOADER_H
