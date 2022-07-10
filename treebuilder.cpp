#include <cstddef>
#include <iostream>
#include <sstream>
#include "heapbuilder.h"
#include "treebuilder.h"
Node::Node(char letter, int freq) 
{
    this->letter = letter;
    this->freq = freq;
    this->left = NULL;
    this->right = NULL;
}

int Node::sum() 
{
    int out = this->freq;
    if (this->left)
        out += this->left->sum();
    if (this->right)
        out += this->right->sum();
    return out;
}

char Node::getLetter() 
{
    return this->letter;
}

int Node::getFreq() 
{
    return this->freq;
}

bool Node::operator>(Node other)
{
    return this->freq > other.freq;
}

bool Node::operator<(Node other)
{
    return this->freq < other.freq;
}

bool Node::operator==(Node other)
{
    return this->letter == other.letter &&
        this->freq == other.freq;
}

Node huffTreeGen(Heap & heap)
{
    if (heap.size() == 1) 
        return heap.remove();
    Node l = heap.remove();
    Node r = heap.remove();
    Node i = Node('\0', l.getFreq() + r.getFreq());
    i.left = &l;
    i.right = &r;
    heap.insert(i);
    return huffTreeGen(heap);
}

bool find(Node* huff, char element)
{
    if (!huff->left && !huff->right)
        return huff->getLetter() == element;
    if (huff->left) 
    {
        bool found = find(huff->left, element);
        if (!found && huff->right)
            found = find(huff->right, element);
        return found;
    }
    return find(huff->right, element);
}

string huffCode(Node* huff, string str)
{
    string out = "";
    if (!huff)
        return out;
    if (huff->getLetter() != '\0') {
        out += (huff->getLetter() + ":" + str + '\0');
        return out;
    }
    out += huffCode(huff->left, str+"0");
    out += huffCode(huff->right, str+"1");
    return out;
}

vector<string> huffCodes(Node* huff)
{
    //string split from
    //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c/14266139#14266139
    vector<string> out;
    cout << "Begin code string generation" << endl;
    string codes = huffCode(huff, "");
    cout << "Code string generation complete" << endl;
    string curLine;
    stringstream ss(codes);
    int cnt = 0;
    while (getline(ss, curLine, '\0'))
        out.push_back(curLine);
    cout << "Code count: " << out.size() << endl;
    return out;
}

vector<string> codes(vector<char> & alphabet, vector<int> & frequencies) 
{
    vector<Node> nodes;
    for (int i = 0; i < alphabet.size(); i++) 
        nodes.push_back(Node(alphabet[i], frequencies[i]));
    Heap h = Heap(nodes);
    Node huffTree = huffTreeGen(h);
    vector<string> output = huffCodes(&huffTree);
    cout << "Code generation complete" << endl;
    return output;
}