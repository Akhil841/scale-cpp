#include "heapbuilder.h"
Heap::Heap()
{
    heap = vector<Node>();
}

Heap::Heap(vector<Node> & nodes)
{
    heap = nodes;
    for (int i = heap.size() - 1; i >= 0; i--)
        percolateDown(i);
}

void Heap::insert(Node node)
{
    heap.push_back(node);
    percolateUp(heap.size() - 1);
}

Node Heap::peek()
{
    if (!heap.size())
        return Node('\0', -1);
    return heap[0];
}

Node Heap::remove()
{
    if (!heap.size())
        return Node('\0', -1);
    return deleteIndex(0);
}

int Heap::size()
{
    return heap.size();
}

void Heap::clear()
{
    heap = vector<Node>();
}

void Heap::swap(int from, int to)
{
    Node temp = heap[from];
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

Node Heap::deleteIndex(int index)
{
    if (index == heap.size()-1) 
    {
        /*Node* output = &heap[index];
        vector<Node>::iterator t;
        t = heap.begin();
        for (int i = 0; i <= index; i++)
            t++;
        heap.erase(t);*/
        Node output = heap[heap.size() - 1];
        heap.pop_back();
        return output;
    }
    Node output = heap[index];
    heap[index] = heap[heap.size() - 1];
    heap.pop_back();
    if (output > heap[index])
        percolateUp(index);
    else
        percolateDown(index);
    return output;
}