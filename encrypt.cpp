#include "encrypt.h"
#include "treelib.h"
#include <algorithm>

void encrypt(IStreamWrapper & in, OStreamWrapper & out)
{
    //(frequency, symbol) tuple vector
    std::vector<std::pair<long unsigned int, unsigned char>> tuples;
    //size of file
    long unsigned int filesize = in.size();
    //do nothing if empty file
    if (!filesize)
        return;
    //get list of chars and list of freqs
    int cur;
    //generate tuple stuff
    while ((cur = in.readByte()) != EOF)
    {
        bool cont = false;
        for (auto it = tuples.begin(); it != tuples.end(); it++)
        {
            if (it->second == (cur & 0xFF))
            {
                it->first++;
                cont = true;
                break;
            }
        }
        if (cont)
            continue;
        tuples.push_back(std::pair<long unsigned int, unsigned char>(1, (cur & 0xFF)));
    }
    //build huffman tree
    Tree tree;
    tree.build(tuples);
    //tree.codeslong();
    //serialize huffman tree
    std::vector<short> srzTree = tree.serialize();
    //keep track of how many bits are written
    long unsigned int bitct = 0;
    //write serialized tree to output file
    for (auto it = srzTree.begin(); it != srzTree.end(); it++)
    {
        char top = char(((*it) & 0xFF00) >> 8);
        top &= 0x0F;
        //write node header
        out.writeBit(char((top & 0x10) >> 1));
        bitct++;
        out.writeBit(char((top & 0x01)));
        bitct++;
        //write each byte individually
        unsigned char node = char((*it) & 0x00FF);
        for (int i = 0; i < 8; i++)
        {
            out.writeBit((node >> i) & 0x01);
            bitct++;
        }
    }
    out.writeBit(1);
    out.writeBit(1);
    bitct += 2;
    //write 0s to space out filesize
    for (long unsigned int i = 0; i < (8 - (bitct % 8)); i++)
    {
        out.writeBit(0);
    }
    //write filesize
    out.writeLong(filesize);
    //create unordered_map with all codes for writing
    tree.initCodes();
    //reset reader
    in.reset();
    //write each character
    while ((cur = in.readByte()) != EOF)
    {
        tree.encode(cur, out);
    }
}