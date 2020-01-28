#ifndef _KDTREE_
#define _KDTREE_

#include <vector>
#include "node.h"
#include "sort.h"

template <typename T>
class Node;

template <typename T>
class KDTree
{
    private:
        Node<T>* root;
        int dim;
    private:
        Node<T>* _build(Node<T>* root, PointND<T>** arr_pts, int num_pts, bool (*compare)(PointND<T>*, PointND<T>*, int), int depth = 0);
        void _clean(Node<T>* &root);
        void clean();
        bool _search(Node<T>* root, PointND<T>* pt, int depth = 0);
        Node<T>* _insert(Node<T>* root, PointND<T>* pt, int depth = 0);
        Node<T>* _findMinNode(Node<T>* root, int axis, int depth = 0);
        Node<T>* _remove(Node<T>* root, PointND<T>* pt, int depth = 0);
        void _printNLR(Node<T>* root);
    public:
        KDTree(int _dim);
        ~KDTree();
        void setDim(int _dim);
        bool search(PointND<T>* pt);
        void insert(PointND<T>* pt);
        void build(vector<PointND<T>*> &arr_pts, int depth = 0);
        void printNLR();
        void remove(PointND<T>* pt);
};

template <typename T>
KDTree<T>::KDTree(int _dim):root(nullptr), dim(_dim){}

template <typename T>
void KDTree<T>::_clean(Node<T>* &root)
{
    if (!root)
        return;
    _clean(root->pLeft);
    _clean(root->pRight);
    delete root;
    root = nullptr;
}

template <typename T>
void KDTree<T>::setDim(int _dim)
{
    if (root)
    {
        clean();
    }
    this->dim = _dim;
}

template <typename T>
void KDTree<T>::clean()
{
    _clean(root);
    root = nullptr;
}

template <typename T>
KDTree<T>::~KDTree()
{
    if (root)
    {
        clean();
    }
}

template <typename T>
bool KDTree<T>::_search(Node<T>* root, PointND<T>* pt, int depth)
{
    if (!root)
        return false;
    if (*(root->location) == *pt)
        return true;
    int axis = depth % dim;
    if (pt->getAtAxis(axis) < root->location->getAtAxis(axis))
        return _search(root->pLeft, pt, depth + 1);
    return _search(root->pRight, pt, depth + 1);
}

template <typename T>
bool KDTree<T>::search(PointND<T>* pt)
{
    return _search(root, pt);
}

template <typename T>
Node<T>* KDTree<T>::_insert(Node<T>* root, PointND<T>* pt, int depth)
{
    if (!root)
    {
        root = new Node<T>();
        root->location = pt;
        return root;
    }
    int axis = depth % dim;
    if (pt->getAtAxis(axis) < root->location->getAtAxis(axis))
        root->pLeft = _insert(root->pLeft, pt, depth + 1);
    else
        root->pRight = _insert(root->pRight, pt, depth + 1);
    return root;
}

template <typename T>
void KDTree<T>::insert(PointND<T>* pt)
{
    root = _insert(root, pt);
}

template <typename T>
Node<T>* KDTree<T>::_build(Node<T>* root, PointND<T>** arr_pts, int num_pts, bool (*compare)(PointND<T>*, PointND<T>*, int), int depth)
{
    if (num_pts == 0)
        return nullptr;
    int axis = depth % dim;
    MergeSort<PointND<T>*>::sort(arr_pts, num_pts, compare, axis);
    int mid = num_pts / 2;
    if (!root)
        root = new Node<T>();
    root->location = arr_pts[mid];
    root->pLeft  = _build(root->pLeft , arr_pts, mid, compare, depth + 1);
    root->pRight = _build(root->pRight, arr_pts + mid + 1, num_pts - mid - 1, compare, depth + 1);
    return root;
}

template <typename T>
void KDTree<T>::build(vector<PointND<T>*> &ls_pts, int depth)
{
    if (root)
    {
        clean();
    }
    auto compare = [](PointND<T>* a, PointND<T>* b, int axis) -> bool
    {
        if (!a)
            return true;
        else if (!b)
            return false;
        return a->getAtAxis(axis) < b->getAtAxis(axis);
    };
    root = _build(root, ls_pts.data(), ls_pts.size(), compare);
}

template <typename T>
Node<T>* KDTree<T>::_findMinNode(Node<T>* root, int axis, int depth)
{
    if (!root)
        return nullptr;
    int dp = depth % dim;
    if (dp == axis)
    {
        if (root->pLeft)
            return _findMinNode(root->pLeft, axis, depth + 1);
        return root;
    }
    return minNode(root, _findMinNode(root->pLeft, axis, depth + 1), _findMinNode(root->pRight, axis, depth + 1), axis);
}

template <typename T>
Node<T>* KDTree<T>::_remove(Node<T>* root, PointND<T>* pt, int depth)
{
    if (!root)
        return nullptr;
    int dp = depth % dim;
    if (*root->location == *pt)
    {
        if (root->pRight)
        {
            Node<T>* min = _findMinNode(root->pRight, dp);
            *root->location = *min->location;
            root->pRight = _remove(root->pRight, min->location, depth + 1);
        }
        else if (root->pLeft)
        {
            Node<T>* min =_findMinNode(root->pLeft, dp);
            *root->location = *min->location;
            root->pRight = _remove(root->pLeft, min->location, depth + 1);
        }
        else
        {
            delete root;
            return nullptr;
        }
        return root;
    }
    if (pt->getAtAxis(dp) < root->location->getAtAxis(dp))
        root->pLeft = _remove(root->pLeft, pt, depth + 1);
    else
        root->pRight = _remove(root->pRight, pt, depth + 1);
    return root;
}

template <typename T>
void KDTree<T>::remove(PointND<T>* pt)
{
    root = _remove(root, pt);
}

template <typename T>
void KDTree<T>::printNLR()
{
  if (!root) return;
  _printNLR(root);
}

template <typename T>
void KDTree<T>::_printNLR(Node<T>* root)
{
  if (!root)
  {
    std::cout << "Blank\n";
    return;
  }
  root->print();

  _printNLR(root->pLeft);
  _printNLR(root->pRight);
}

#endif
