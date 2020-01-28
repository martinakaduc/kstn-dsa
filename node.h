#ifndef _NODE_
#define _NODE_

#include "point.h"
#include "kdtree.h"

template <typename T>
class KDTree;

template <typename T>
class Node
{
    private:
        PointND<T>* location;
        Node<T>* pLeft;
        Node<T>* pRight;
        friend class KDTree<T>;
        template <typename K>
        friend Node<K>* minNode(Node<K>*, Node<K>*, Node<K>*, int);
    public:
        Node();
        ~Node();
        void print();

};

template <typename T>
Node<T>::Node():location(nullptr), pLeft(nullptr), pRight(nullptr){}


template <typename T>
Node<T>* minNode(Node<T>* x, Node<T>* y, Node<T>* z, int axis)
{
    Node<T>* min = x;
    if (y && y->location->getAtAxis(axis) < min->location->getAtAxis(axis))
        min = y;
    if (z && z->location->getAtAxis(axis) < min->location->getAtAxis(axis))
        min = z;
    return min;
}

template <typename T>
Node<T>::~Node()
{
    if (location)
    {
        delete location;
        location = nullptr;
    }
    if (pLeft)
    {
        delete pLeft;
        pLeft = nullptr;
    }
    if (pRight)
    {
        delete pRight;
        pRight = nullptr;
    }
}

template <typename T>
void Node<T>::print() {
  location->print();
}

#endif
