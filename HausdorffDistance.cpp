//
//  HausdorffDistance.cpp
//  MeshSimilarity
//
//  Created by Vaibhav Dabaria on 18/06/19.
//  Copyright © 2019 Vaibhav Dabaria. All rights reserved.
//

#include <iostream>
#include "HausdorffDistance.h"

double HausdorffDistance(std::vector<Point_3d> vertices1, std::vector<Point_3d> & vertices2)
{
    double hd = 0.0;
    
    // Build kd-tree for vertices1 and vertices2
    kd_tree ktree1(vertices1);
    kd_tree ktree2(vertices2);
    
    double h_12 = -1.0; // Hausdorff distance between 1 and 2
    double h_21 = -1.0; // Hausdorff distance between 2 and 1
    for(auto point1 : vertices1)
    {
        double distFound;
        ktree2.FindNearestNeighbour(point1, distFound);
        if(distFound > h_12)
            h_12 = distFound;
    }
    
    for(auto point2 : vertices2)
    {
        double distFound;
        ktree1.FindNearestNeighbour(point2, distFound);
        if(distFound > h_21)
            h_21 = distFound;
    }
    
    hd = std::max(h_12, h_21); // returning Hausdorff distance
    
    return hd;
}

