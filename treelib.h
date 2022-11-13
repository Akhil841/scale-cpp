#pragma once
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "util.h"

class Tree
{
    private:
        //the tree's root
        Node* root;
        //maps ints to their huffman codes
        std::unordered_map<int, std::string> hcodes;
        //maps huffman codes to their corresponding characters
        std::unordered_map<std::string, int> symbs;
    public:
        //constructor
        Tree();
        ~Tree();
        //build a huffman tree from a set of (frequency, symbol) tuples
        void build(std::vector<std::pair<long unsigned int, unsigned char>>& freqs);
        //build a huffman tree from an encoded set of nodes
        void build(std::vector<short>& encNodes);
        //Decode a set of nodes
        Node* dcBuildHelper(std::vector<short>::iterator* nit, std::vector<short>::iterator end);
        //Encode a symbol and write it to the provided OStreamWrapper
        void encode(unsigned char symbol, OStreamWrapper & out);
        //Decode the given input stream and write it to the given output stream
        //Assumes input starts at data
        void decode(IStreamWrapper& in, OStreamWrapper& out, unsigned long int filesize);
        //(For debugging) Prints all nodes and their relationships
        void codeslong();
        //helper for codeslong
        void codeslong(Node* node);
        //populate hcodes
        void initCodes();
        //populate symbs
        void initSymbs();
        //serialize the tree
        std::vector<short> serialize();
        //helper for initCodes
        void icHelper(Node* n, std::string s);
};