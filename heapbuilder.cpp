#include "heapbuilder.h"
Heap::Heap()
{
    heap = vector<INode>();
}

Heap::Heap(vector<INode> & nodes)
{
    heap = nodes;
    for (int i = heap.size() - 1; i >= 0; i--)
        percolateDown(i);
}

void Heap::insert(INode node)
{
    heap.push_back(node);
    percolateUp(heap.size() - 1);
}

INode Heap::peek()
{
    if (!heap.size())
        return IntNode(-1);
    return heap[0];
}

INode Heap::remove()
{
    if (!heap.size())
        return IntNode(-1);
    return deleteIndex(0);
}

int Heap::size()
{
    return heap.size();
}

void Heap::clear()
{
    heap = vector<INode>();
}

void Heap::swap(int from, int to)
{
    INode temp = heap[from];
    heap[from] = heap[to];
    heap[to] = temp;
}

int Heap::getParentI(int index)
{
    return (index - 1)/2;
}

int Heap::getLChildI(int index)
{
    return 2 * index + 1;
}

int Heap::getRChildI(int index)
{
    return 2 * index + 2;
}

int Heap::getMinChildI(int index)
{
    //leaf
    if (getLChildI(index) >= heap.size() && getRChildI(index) >= heap.size())
        return -1;
    //only has one child (must be left)
    if (getRChildI(index) >= heap.size())
        return getLChildI(index);
    //rchild < lchild
    if (heap[getRChildI(index)] < heap[getLChildI(index)])
        return getRChildI(index);
    //lchild <= rchild
    return getLChildI(index);
}

void Heap::percolateUp(int index)
{
    if (index == 0) 
        return;
    if (heap[getParentI(index)] < heap[index])
        return;
    swap(getParentI(index), index);
    percolateUp(getParentI(index));
}

void Heap::percolateDown(int index)
{
    if (getMinChildI(index) == -1) 
        return;
    if (heap[getLChildI(index)] > heap[index] && 
    heap[getRChildI(index)] > heap[index])
        return;
    int nextPD = getMinChildI(index);
    swap(nextPD, index);
    percolateDown(nextPD);
}

INode Heap::deleteIndex(int index)
{
    if (index == heap.size()-1) 
    {
        INode output = heap[heap.size() - 1];
        heap.pop_back();
        return output;
    }
    INode output = heap[index];
    heap[index] = heap[heap.size() - 1];
    heap.pop_back();
    if (output > heap[index])
        percolateUp(index);
    else
        percolateDown(index);
    return output;
}