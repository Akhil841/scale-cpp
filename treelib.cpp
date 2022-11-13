#include "treelib.h"
#include <algorithm>

void deleteHelper(Node* n)
{
    if (!n)
        return;
    if (n->l)
        deleteHelper(n->l);
    if (n->r)
        deleteHelper(n->r);
    delete n;
}

Tree::Tree() : root(nullptr) {}

Tree::~Tree()
{
    deleteHelper(root);
}

//checks if a node is a leaf
bool isleaf(Node* node)
{
    return !(node->l && node->r);
}

void Tree::icHelper(Node* n, std::string s)
{
    if (isleaf(n))
    {
        hcodes[n->symbol] = s;
    }
    if (n->l)
        icHelper(n->l, s + "0");
    if (n->r)
        icHelper(n->r, s + "1");
}

void Tree::initCodes()
{
    icHelper(root, "");
}

void Tree::initSymbs()
{
    initCodes();
    for (auto it = hcodes.begin(); it != hcodes.end(); it++)
    {
        symbs[it->second] = it->first;
    }
}

void Tree::codeslong()
{
    codeslong(root);
}

void Tree::codeslong(Node* node)
{
    if (isleaf(node))
    {
        std::cout << "Leaf (value " << char(node->symbol) << ", count " << node->count << ")" << std::endl;
        return;
    }
    std::cout << "Internal node with value " << node->count << " has: ";
    if (node->l)
    {
        std::cout << "left child ";
        if (isleaf(node->l))
            std::cout << "Leaf (value " << char(node->l->symbol) << ", count " << node->l->count << ")" << std::endl;
        else
            std::cout << "Internal node with value " << node->l->count << std::endl;
    }
    if (node->r)
    {
        std::cout << "right child ";
        if (isleaf(node->r))
            std::cout << "Leaf (value " << char(node->r->symbol) << ", count " << node->r->count << ")" << std::endl;
        else
            std::cout << "Internal node with value " << node->r->count << std::endl;
    }
    if (node->l)
        codeslong(node->l);
    if (node->r)
        codeslong(node->r);
}

//recursive huffman tree generator
Node* treegen(std::priority_queue<Node*, std::vector<Node*>, NodeComp> pqueue)
{
    if (pqueue.size() == 1)
    {
        Node* out = pqueue.top();
        pqueue.pop();
        return out;
    }
    Node* le = pqueue.top();
    pqueue.pop();
    Node* ri = pqueue.top();
    pqueue.pop();
    Node* i = new Node(le->count + ri->count, 0);
    i->l = le;
    i->r = ri;
    le->p = i;
    ri->p = i;
    pqueue.push(i);
    return treegen(pqueue);
}

void Tree::build(std::vector<std::pair<long unsigned int, unsigned char>>& freqs)
{
    //convert all pairs to hcnodes and store in vector
    std::vector<Node*> nodes;
    for (auto it = freqs.begin(); it != freqs.end(); it++)
        nodes.push_back(new Node(it->first, it->second));
    //create priority_queue from nodes
    std::priority_queue<Node*, std::vector<Node*>, NodeComp> minpqueue(nodes.begin(), nodes.end()); 
    //generate huffman tree
    root = treegen(minpqueue);
}

//helper method for serialize
std::vector<short> serializeHelper(Node* cur)
{
    std::vector<short> out;
    //if current node is null
    if (!cur)
    {
        //push 0x0100 to distinguish from null leaf
        //and internal character
        out.push_back(0x0100);
    }
    else
    {
        //push current node
        //if current node is internal, push 0x0200
        //to distinguish from null leaf and null node
        if (!isleaf(cur))
            out.push_back(0x0200);
        else
            out.push_back(short(cur->symbol));
        //call on left
        std::vector<short> le = serializeHelper(cur->l);
        //call on right
        std::vector<short> ri = serializeHelper(cur->r);
        //merge l, then r to out
        for (auto it = le.begin(); it != le.end(); it++)
            out.push_back(*it);
        for (auto it = ri.begin(); it != ri.end(); it++)
            out.push_back(*it);
    }
    return out;
}

std::vector<short> Tree::serialize()
{
    return serializeHelper(root);
}

void Tree::encode(unsigned char symbol, OStreamWrapper & out)
{
    std::string hcode = hcodes[symbol];
    for (unsigned int i = 0; i < hcode.length(); i++)
    {
        char c = hcode[i];
        if (c == '1')
            out.writeBit(1);
        else
            out.writeBit(0);
    }
}

void Tree::build(std::vector<short>& encNodes)
{
    std::vector<short>::iterator begin = encNodes.begin();
    root = dcBuildHelper(&begin, encNodes.end());
}

Node* Tree::dcBuildHelper(std::vector<short>::iterator* nit, std::vector<short>::iterator nodesEnd)
{
    if (*nit == nodesEnd)
        return nullptr;
    short cur = *(*nit);
    (*nit)++;
    if (cur == 0x0100)
        return nullptr;
    Node* ro = new Node(0, char(cur & 0x00FF));
    Node* lchild = dcBuildHelper(nit, nodesEnd);
    Node* rchild = dcBuildHelper(nit, nodesEnd);
    ro->l = lchild;
    ro->r = rchild;
    if (lchild)
        lchild->p = ro;
    if (rchild)
        rchild->p = ro;
    return ro;
}

void Tree::decode(IStreamWrapper& input, OStreamWrapper& out, unsigned long int filesize)
{
    char cur;
    long unsigned int numDecoded = 0;
    std::string curstring = "";
    while (((cur = input.readBit()) != -1) && numDecoded < filesize)
    {
        //update current string
        curstring += cur ? "1" : "0";
        //check if it exists in the symbs dictionary
        if (symbs.find(curstring) != symbs.end())
        {
            //if it is, write it to the output file
            out.writeByte(char(symbs[curstring] & 0x000000FF));
            numDecoded++;
            curstring = "";
        }
    }
}