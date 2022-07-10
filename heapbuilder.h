#ifndef _HEAPBUILDER_H
#define _HEAPBUILDER_H
#include "treebuilder.h"
class Heap
{
    public:
        Heap();
        Heap(vector<Node> & nodes);
        Node peek();
        Node remove();
        void insert(Node node);
        int size();
        void clear();
    private:
        vector<Node> heap;
        void swap(int from, int to);
        int getParentI(int index);
        int getLChildI(int index);
        int getRChildI(int index);
        int getMinChildI(int index);
        void percolateUp(int index);
        void percolateDown(int index);
        Node deleteIndex(int index);
};
#endif