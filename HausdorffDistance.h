//
//  HausdorffDistance.h
//
//  Created by Vaibhav Dabaria on 18/06/19.
//  Copyright © 2019 Vaibhav Dabaria. All rights reserved.
//

#ifndef HausdorffDistance_h
#define HausdorffDistance_h

#include "kd_tree.h"

// Calculates Hausdorff Distance between two meshes m1 and m2
double HausdorffDistance(std::vector<Point_3d> vertices1, std::vector<Point_3d> & vertices2);

#endif /* HausdorffDistance_h */
