//
//  Point_3d.h
//  MeshSimilarity
//
//  Created by Vaibhav Dabaria on 17/06/19.
//  Copyright © 2019 Vaibhav Dabaria. All rights reserved.
//

#ifndef Point_3D_h
#define Point_3D_h

class Point_3d
{
public:
    Point_3d();
    Point_3d(double x, double y, double z);
    double DistanceTo(const Point_3d & pt);
    // access x, y and z coordinates with 0, 1 and 2 index respectively
    double &operator[] (int);
    double _x;
    double _y;
    double _z;
};

#endif /* Point_3D_h */
