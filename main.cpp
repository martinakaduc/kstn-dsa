#include <iostream>
#include <vector>
#include "kdtree.h"
using namespace std;

int main()
{
    int dim = 3;

    // Insert a pint into KDTree
    vector<PointND<int>*> arr;
    arr.push_back(new PointND<int>(new int[dim]{5,3,1}, dim));
    arr.push_back(new PointND<int>(new int[dim]{1,7,2}, dim));
    arr.push_back(new PointND<int>(new int[dim]{2,5,8}, dim));
    arr.push_back(new PointND<int>(new int[dim]{3,4,6}, dim));
    arr.push_back(new PointND<int>(new int[dim]{6,1, -1}, dim));
    arr.push_back(new PointND<int>(new int[dim]{7,7}, dim));

    KDTree<int>* tree = new KDTree<int>(dim);

    cout << "==============INSERTING==============\n";
    for (auto pt : arr)
        tree->insert(pt);

    // Print inserted KDTree
    tree->printNLR();

    delete tree;
    cout << "==============DELETED==============\n";

    // Build KDTree using a point list
    tree = new KDTree<int>(dim);
    arr.clear();
    arr.push_back(new PointND<int>(new int[dim]{5,3,1}, dim));
    arr.push_back(new PointND<int>(new int[dim]{1,7,2}, dim));
    arr.push_back(new PointND<int>(new int[dim]{2,5,8}, dim));
    arr.push_back(new PointND<int>(new int[dim]{3,4,6}, dim));
    arr.push_back(new PointND<int>(new int[dim]{6,1, -1}, dim));
    arr.push_back(new PointND<int>(new int[dim]{7,7}, dim));

    cout << "==============BUILDING==============\n";
    tree->build(arr);

    // Print built KDTree
    tree->printNLR();

    // Remove a node from the tree
    cout << "==============REMOVING==============\n";
    tree->remove(new PointND<int>(new int[dim]{5,3,1}, dim));

    // Print KDTree
    tree->printNLR();

    // Search a node if it's available in the tree or not
    cout << "==============SEARCHING==============\n";
    bool isAvai = tree->search(new PointND<int>(new int[dim]{3,4,6}, dim));

    cout << "Search result: " << (isAvai ? "true" : "false") << endl;
    // Print KDTree
    tree->printNLR();

    delete tree;
    tree = nullptr;
    return 0;
}
// (3,4), (5,3), (6,1), (7,7)
