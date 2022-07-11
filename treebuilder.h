#ifndef _TREEBUILDER_H
#define _TREEBUILDER_H
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class INode
{
    public:
        INode* left;
        INode* right;
        INode();
        INode(int freq);
        bool hasLetter();
        int sum();
        bool operator>(INode other);
        bool operator<(INode other);
        bool operator==(INode other);
        int freq;
        virtual ~INode(){};
};

class Node : public INode
{
    using INode::INode;
    public:
        Node(char letter, int freq);
        bool hasLetter();
        bool operator>(INode other);
        bool operator<(INode other);
        bool operator==(INode other);
        char letter;
};

class IntNode : public INode {
    using INode::INode;
    public:
        IntNode(int freq);
        bool hasLetter();
        bool operator>(INode other);
        bool operator<(INode other);
        bool operator==(INode other);
};
vector<string> codes(vector<char> & alphabet, vector<int> & frequencies);
#endif