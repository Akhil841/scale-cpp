#pragma once
#include <fstream>
#include <iostream>
#include <string>

void error(std::string errormsg);

class IStreamWrapper
{
    private:
        std::string filename;
        std::ifstream readfile;
        unsigned char buf;
        unsigned char buf_index;
    public:
        IStreamWrapper(std::string filename);
        bool good() const;
        long unsigned int size() const;
        void reset();
        unsigned long readLong();
        unsigned int readInt();
        int readByte();
        unsigned char readBit();
        bool eof();
};

class OStreamWrapper
{
    private:
        std::ofstream writefile;
        unsigned char buf;
        unsigned char buf_index;
    public:
        OStreamWrapper(std::string filename);
        ~OStreamWrapper();
        bool good() const;
        void writeLong(unsigned long l);
        void writeInt(unsigned int n);
        void writeByte(unsigned char b);
        void writeBit(unsigned char b);
        void flush_bitwise();
        void flush();
};

class Node
{
    public:
        //frequency
        long unsigned int count;
        //symbol
        unsigned char symbol;
        //children
        Node* l;
        Node* r;
        //parent
        Node* p;
        //constructor
        Node(long unsigned int count, unsigned char symbol);
        //comparison operator for sort
        bool operator<(const Node& other);
};

//comparison class
class NodeComp
{
    public:
        bool operator()(Node*&n1, Node*&n2);
};