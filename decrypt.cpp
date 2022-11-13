#include "decrypt.h"
#include "treelib.h"
#include <algorithm>

void decrypt(IStreamWrapper & in, OStreamWrapper & out)
{
    long unsigned int filesize = in.size();
    //return if empty
    if (!filesize)
        return;
    bool cont = true;
    std::vector<short> encNodes;
    //filesize now represents size of output file
    filesize = 0;
    //keep track of all bits read
    unsigned long int bitct = 0;
    //get all encnodes
    while (cont)
    {
        //read node header
        unsigned char b1 = in.readBit();
        bitct++;
        unsigned char b2 = in.readBit();
        bitct++;
        //file is either corrupt or only header is present
        //(both of which are bad)
        if (b1 == -1 || b2 == -1)
        {
            cont = false;
            continue;
        }
        //no node has 11 as header
        if (b1 == 1 && b2 == 1)
        {
            //read enough zeros to space out
            for (long unsigned int i = 0; i < (8 - (bitct % 8)); i++)
            {
                in.readBit();
            }
            //get output filesize
            filesize = in.readLong();
            //we have now reached beginning of data
            cont = false;
            continue;
        }
        //read 8 bits and add to cur
        int cur = 0;
        for (int i = 0; i < 8; i++)
        {
            cur += (in.readBit()) << i;
            bitct++;
        }
        //add to encnodes
        short nodeheader = ((b1 << 1) + b2) << 8;
        encNodes.push_back(nodeheader + cur);
    }
    //construct huffman tree
    Tree tree;
    //build huffman tree
    tree.build(encNodes);
    //initialize symbol dictionary
    tree.initSymbs();
    //decode file
    tree.decode(in, out, filesize);
}