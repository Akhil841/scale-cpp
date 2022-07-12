#include <iostream>
#include "treebuilder.h"
#include <queue>

class compare
{
    public:
        bool operator()(Node* a, Node* b)
        {
            return a->freq > b->freq;
        }
};

Node::Node(char letter, int freq)
{
    this->letter = letter;
    this->freq = freq;
    this->within = false;
}

bool Node::operator>(Node other)
{
    return this->freq > other.freq && !other.within;
}

bool Node::operator<(Node other)
{
    return this->freq < other.freq&& !other.within;
}

bool Node::operator==(Node other)
{
    if (!other.within)
        return this->freq == other.freq;
    return false;
}

Node* huffTreeGen(priority_queue<Node*, vector<Node*>, compare>& pqueue)
{
    if (pqueue.size() == 1) {
        Node* out = pqueue.top();
        pqueue.pop();
        return out;
    }
    Node* l = pqueue.top();
    pqueue.pop();
    Node* r = pqueue.top();
    pqueue.pop();
    Node* i = new Node('\0', l->freq + r->freq);
    i->left = l;
    i->right = r;
    i->within = true;
    pqueue.push(i);
    return huffTreeGen(pqueue);
}

void huffCodes(Node* huff, string str, vector<string>* strings)
{
    if (!huff->within)
    {
        strings->push_back(string(1, huff->letter) + ":" + str);
        return;
    }
    if (huff->left)
    {
        huffCodes(huff->left, str + "0", strings);
    }
    if (huff->right)
    {
        huffCodes(huff->right, str + "1", strings);
    }
}

vector<string>* codes(vector<char>& alphabet, vector<int>& frequencies)
{
    priority_queue<Node*,vector<Node*>,compare> nodes;
    for (int i = 0; i < alphabet.size(); i++) {
        Node* temp = new Node(alphabet[i], frequencies[i]);
        nodes.push(temp);
    }
    Node* huffTree = huffTreeGen(nodes);
    vector<string>* outputs = new vector<string>();
    huffCodes(huffTree, "", outputs);
    return outputs;
}