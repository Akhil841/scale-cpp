#ifndef _HEAPBUILDER_H
#define _HEAPBUILDER_H
#include "treebuilder.h"
class Heap
{
    public:
        Heap();
        Heap(vector<INode> & nodes);
        INode peek();
        INode remove();
        void insert(INode node);
        int size();
        void clear();
    private:
        vector<INode> heap;
        void swap(int from, int to);
        int getParentI(int index);
        int getLChildI(int index);
        int getRChildI(int index);
        int getMinChildI(int index);
        void percolateUp(int index);
        void percolateDown(int index);
        INode deleteIndex(int index);
};
#endif