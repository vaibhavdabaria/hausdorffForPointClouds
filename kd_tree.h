//
//  kd_tree.h
//  MeshSimilarity
//
//  Created by Vaibhav Dabaria on 18/06/19.
//  Copyright © 2019 Vaibhav Dabaria. All rights reserved.
//

#ifndef kd_tree_h
#define kd_tree_h
#include "Point_3d.h"
#include <vector>

class node
{
public:
    node(Point_3d point);
    Point_3d _point;
    node * _left;
    node * _right;
};

class kd_tree
{
private:
    node * _root;
    std::vector<Point_3d> _pointList;
    
    node * MakeTree(int start_id, int end_id, int level);
    void MakeTree();
    int FindMedian(int start_id, int end_id, int level);
    void FindNearestNeighbour(node * root, Point_3d ptToFind, int level, node ** nearNode, double &bestDist);
    void Erase(node * n);
    
public:
    // Construct a kd tree with a vector of 3d points
    kd_tree(const std::vector<Point_3d> &pts);
    // Destructor
    ~kd_tree();
    // return root of the tree
    inline node * GetRoot() { return _root;};
    // return pointer to nearest node to ip_pt
    node * FindNearestNeighbour(Point_3d ip_pt, double & distToFoundPt);
};

bool Compare_x(Point_3d p1, Point_3d p2);
bool Compare_y(Point_3d p1, Point_3d p2);
bool Compare_z(Point_3d p1, Point_3d p2);

#endif /* kd_tree_h */
