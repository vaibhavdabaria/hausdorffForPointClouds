//
//  kd_tree.cpp
//  MeshSimilarity
//
//  Created by Vaibhav Dabaria on 18/06/19.
//  Copyright © 2019 Vaibhav Dabaria. All rights reserved.
// reference: https://rosettacode.org/wiki/K-d_tree
//
#include "kd_tree.h"
#include <algorithm>

#define DIMENSION 3
#define TOL 1.0e-9

node::node(Point_3d point)
{
    _point = point;
    _left = nullptr; _right = nullptr;
}

kd_tree::kd_tree(const std::vector<Point_3d> &points)
{
    _pointList = points;
    MakeTree();
}

kd_tree::~kd_tree()
{
    if(_root)
        Erase(_root);
}

// Build a kd tree recursively from a vector of 3d point starting from start_id till end_id
// level refers to the level in the tree:
//                    level%3 == 0 for x-partition
//                    level%3 == 1 for y-partition
//                    level%3 == 2 for z-partition
node * kd_tree::MakeTree(int start_id, int end_id, int level)
{
    node * root = nullptr;
    if(end_id <= start_id)
        return root;
    
    int id = FindMedian(start_id, end_id, level);
    if(id != -1)
        root = new node(_pointList[id]);
    
    if(root)
    {
        level++;
        level = level % DIMENSION;
        root->_left = MakeTree(start_id, id, level);
        root->_left = MakeTree(id+1, end_id, level);
    }
    return root;
}

// If level == 0, then finds medians considering x coordinate between start_id and end_id
// If level == 1, then finds medians considering y coordinate between start_id and end_id
// If level == 2, then finds medians considering z coordinate between start_id and end_id
int kd_tree::FindMedian(int start_id, int end_id, int level)
{
    if(end_id < start_id)
        return -1;
    
    if(end_id - start_id == 1)
        return start_id;
    
    int median = (start_id + end_id)/2;
    bool (*Compare_func)(Point_3d, Point_3d);
    if(level == 0)
        Compare_func = Compare_x;
    else if (level == 1)
        Compare_func = Compare_y;
    else
        Compare_func = Compare_z;
    
    std::nth_element(_pointList.begin()+start_id, _pointList.begin()+median, _pointList.begin()+end_id, Compare_func);
    
    return median;
}

// Comparison functions
bool Compare_x(Point_3d p1, Point_3d p2)
{
    return (p1._x < p2._x);
}

bool Compare_y(Point_3d p1, Point_3d p2)
{
    return (p1._y < p2._y);
}

bool Compare_z(Point_3d p1, Point_3d p2)
{
    return (p1._z < p2._z);
}


// Build kd tree out of pts
void kd_tree::MakeTree()
{
    _root = MakeTree(0, _pointList.size()-1, 0);
}

// Memory management
void kd_tree::Erase(node * n)
{
    if(n)
    {
        Erase(n->_left);
        Erase(n->_right);
        delete n;
        n = nullptr;
    }
    else
        return;
}

node * kd_tree::FindNearestNeighbour(Point_3d ip_pt, double & odistToPtFound)
{
    node * nearNode = NULL;
    FindNearestNeighbour(_root, ip_pt, 0, &nearNode, odistToPtFound);
    return nearNode;
}

void kd_tree::FindNearestNeighbour(node * root, Point_3d ptToFind, int level, node ** nearNode, double &bestDist)
{
    if(!root)
        return;
    
    Point_3d pt = root->_point;
    double dist = pt.DistanceTo(ptToFind);
    double signedDist = pt[level] - ptToFind[level];
    double signedDistSq = signedDist*signedDist;
    
    if((*nearNode == NULL) || dist < bestDist)
    {
        *nearNode = root;
        bestDist = dist;
    }
    
    if(bestDist < TOL)
        return;
    
    ++level;
    if(level >= DIMENSION)
        level = 0;
    
    if(signedDist > 0)
        FindNearestNeighbour(root->_left, ptToFind, level, nearNode, bestDist);
    else
        FindNearestNeighbour(root->_right, ptToFind, level, nearNode, bestDist);
    
    if(signedDistSq >= bestDist)
        return;
    
    if(signedDist > 0)
        FindNearestNeighbour(root->_right, ptToFind, level, nearNode, bestDist);
    else
        FindNearestNeighbour(root->_left, ptToFind, level, nearNode, bestDist);
}

