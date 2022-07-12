#pragma once
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Node
{
public:
    Node* left;
    Node* right;
    bool within;
    char letter;
    int freq;
    Node(char letter, int freq);
    bool operator>(Node other);
    bool operator<(Node other);
    bool operator==(Node other);
    virtual ~Node() {};
};
vector<string>* codes(vector<char>& alphabet, vector<int>& frequencies);