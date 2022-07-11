#include <iostream>
#include "heapbuilder.h"
#include "treebuilder.h"

INode::INode()
{
    this->freq = 0;
    this->left = nullptr;
    this->right = nullptr;
}

INode::INode(int freq)
{
    this->freq = freq;
    this->left = nullptr;
    this->right = nullptr;
}

int INode::sum()
{
    int out = this->freq;
    if (this->left)
        out += this->left->freq;
    if (this->right)
        out += this->right->freq;
    return out;
}

bool INode::hasLetter()
{
    return false;
}

bool INode::operator<(INode other)
{
    return this->freq < other.freq;
}

bool INode::operator>(INode other)
{
    return this->freq > other.freq;
}

bool INode::operator==(INode other)
{
    return this->freq == other.freq;
}

Node::Node(char letter, int freq) 
{
    this->letter = letter;
}

bool Node::hasLetter()
{
    return true;
}

bool Node::operator>(INode other)
{
    return this->freq > other.freq && other.hasLetter();
}

bool Node::operator<(INode other)
{
    return this->freq < other.freq && other.hasLetter();
}

bool Node::operator==(INode other)
{
    if (other.hasLetter())
        return this->freq = other.freq;
    return false;
}

IntNode::IntNode(int freq)
{
    this->freq = freq;
}

bool IntNode::hasLetter()
{
    return false;
}

bool IntNode::operator>(INode other)
{
    return this->freq > other.freq && !other.hasLetter();
}

bool IntNode::operator<(INode other)
{
    return this->freq < other.freq && !other.hasLetter();
}

bool IntNode::operator==(INode other)
{
    return this->freq == other.freq && !other.hasLetter();
}

INode huffTreeGen(Heap & heap)
{
    if (heap.size() == 1) 
        return heap.remove();
    INode l = heap.remove();
    INode r = heap.remove();
    INode i = IntNode(l.freq + r.freq);
    i.left = &l;
    i.right = &r;
    heap.insert(i);
    return huffTreeGen(heap);
}

/*bool find(INode* huff, char element)
{
    if (!huff->left && !huff->right)
        return huff->letter == element;
    if (huff->left) 
    {
        bool found = find(huff->left, element);
        if (!found && huff->right)
            found = find(huff->right, element);
        return found;
    }
    return find(huff->right, element);
}*/

vector<string> huffCodes(INode* huff, string str)
{
    vector<string> out = vector<string>();
    if (!huff)
        return out;
    if (huff->hasLetter()) 
    {
        Node* temp = dynamic_cast<Node*>(huff);
        if (temp) {
            out.push_back(temp->letter + ":" + str);
            return out;
        }
        throw 1;
    }
    vector<string> left = huffCodes(huff->left, str+"0");
    out.reserve(out.size() + left.size());
    out.insert(out.end(), out.begin(), out.end());
    out.insert(out.end(), left.begin(), left.end());
    vector<string> right = huffCodes(huff->right, str+"1");
    out.reserve(out.size() + right.size());
    out.insert(out.end(), out.begin(), out.end());
    out.insert(out.end(), right.begin(), right.end());
    return out;
}

vector<string> huffCodes(INode* huff)
{
    return huffCodes(huff, "");
}

vector<string> codes(vector<char> & alphabet, vector<int> & frequencies) 
{
    vector<INode> nodes;
    for (int i = 0; i < alphabet.size(); i++) 
        nodes.push_back(Node(alphabet[i], frequencies[i]));
    Heap h = Heap(nodes);
    INode huffTree = huffTreeGen(h);
    vector<string> output = huffCodes(&huffTree);
    return output;
}