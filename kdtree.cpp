#include "mergesort.h"

template typename<T>
class PointND {
  T* pos;
  int dim;
  PointND() : pos(nullptr), dim(0) {}
  PointND(int _dim) {
    this->dim = _dim;
    this->pos = new T[this->dim];
  }
  PointND(T* _pos, int _dim) {
    this->dim = _dim;
    this->pos = _pos;
  }
  ~PointND() {
    delete[] this->pos;
    this->pos = nullptr;
  }
  bool operator == (PointND const &obj) {
    if (this->dim != obj->dim) return false;

    bool res = true;
    for (int i = 0; i < this->dim; i++) {
      if (this->pos[i] != obj->pos[i]) {
        res = false;
        break;
      }
    }

    return res;
  }
  PointND operator = (PointND const &obj) {
    if (this->pos != nullptr) {
      delete[] this->pos;
    }

    this->dim = obj->dim;
    this->pos = new T[this->dim];
    for (int i = 0; i < this->dim; i++) {
      this->pos[i] != obj->pos[i]
    }

    return this;
  }
}

template typename<T>
class Node {
  T location;
  Node* left;
  Node* right;
public:
  Node() : location(-1), left(nullptr), right(nullptr) {}
  ~Node() {
    delete this->left;
    delete this->right;
    this->left = nullptr;
    this->right = nullptr;
  }

  Node* construct(T* &point_list, int low, int high, int depth, int dim) {
    if (high < low) return nullptr;

    int axis = depth % dim;
    this->sort_point_axis(point_list, low, high, axis, dim);

    int median = (high + low) / 2;
    this->location = point_list[median];

    Node* _left = new Node();
    Node* _right = new Node();
    this->left = _left->construct(point_list, low, median - 1, depth + 1, dim);
    this->right = _right->construct(point_list, median + 1, high, depth + 1, dim);

    return this;
  }

  void sort_point_axis(T* &point_list, int low, int high, int axis, int dim) {
    
  }
}

template typename<T>
class KDTree {
  Node<T>* root;
  T* point_list;
  int dim;
public:
  KDTree() : root(nullptr), point_list(nullptr), dim(0) {}
  ~KDTree() {
    this->clean();
  }

  void clean() {
    delete this->root;
    delete this->point_list;
    this->root = nullptr;
    this->point_list = nullptr;
    this->dim = 0;
  }

  void build(T* &point_list, int size, int dim) {
    if (this->root != nullptr)
      clean()
    this->point_list = point_list;
    this->dim = dim;

    this->root = this->root->construct(point_list, 0,  size-1, 0, dim);
  }
}
