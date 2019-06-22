//
//  Point_3d.cpp
//  MeshSimilarity
//
//  Created by Vaibhav Dabaria on 17/06/19.
//  Copyright © 2019 Vaibhav Dabaria. All rights reserved.
//

#include "Point_3d.h"
#include <math.h>

Point_3d::Point_3d()
{
    _x = 0.0; _y = 0.0; _z = 0.0;
}

Point_3d::Point_3d(double x, double y, double z)
{
    _x = x; _y = y; _z = z;
}

double Point_3d::DistanceTo(const Point_3d & pt)
{
    double dx = (_x - pt._x)*(_x - pt._x);
    double dy = (_y - pt._y)*(_y - pt._y);
    double dz = (_z - pt._z)*(_z - pt._z);
    return sqrt(dx + dy + dz);
}

double & Point_3d::operator[] (int index)
{
    if(index < 0 || index > 2)
        throw 0;
    if(index == 0)
        return _x;
    else if(index == 1)
        return _y;
    else
        return _z;
}
