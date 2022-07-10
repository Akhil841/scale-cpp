#ifndef _TREEBUILDER_H
#define _TREEBUILDER_H
#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Node 
{
    public:
        Node* left;
        Node* right;
        Node(char letter, int freq);
        int sum();
        char getLetter();
        int getFreq();
        bool operator>(Node other);
        bool operator<(Node other);
        bool operator==(Node other);
    private:
        char letter;
        int freq;
};
vector<string> codes(vector<char> & alphabet, vector<int> & frequencies);
#endif