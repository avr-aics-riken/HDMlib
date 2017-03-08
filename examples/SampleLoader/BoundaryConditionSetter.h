/*
###################################################################################
#
# HDMlib - Data management library for hierarchical Cartesian data structure
#
# Copyright (c) 2014-2017 Advanced Institute for Computational Science (AICS), RIKEN.
# All rights reserved.
#
# Copyright (c) 2017 Research Institute for Information Technology (RIIT), Kyushu University.
# All rights reserved.
#
###################################################################################
 */

#ifndef BOUNDARY_CONDITION_SETTER_H
#define BOUNDARY_CONDITION_SETTER_H

#include "BCMTools.h"
#include "BoundaryConditionSetterBase.h"
#include "BCMOctree.h"
#include "BoundaryInfo.h"

class BoundaryConditionSetter : public BoundaryConditionSetterBase {


public:

  BoundaryConditionSetter() {}

  ~BoundaryConditionSetter() {}

  BoundaryInfo* operator() (const Node* node, const BCMOctree* tree) {
    BoundaryInfo* boundaryInfo = new BoundaryInfo[NUM_FACE];

    // BoundaryInfoの初期値は，type=INNER, id=-1

    // 境界条件の設定
    for (int i = 0; i < NUM_FACE; i++) {
      Face face = Face(i);
      if (tree->checkOnOuterBoundary(node, face)) {
        boundaryInfo[face].setType(BoundaryInfo::DIRICHLET);
        boundaryInfo[face].setID(0);
      }
    }

    return boundaryInfo;
  }

};


#endif // BOUNDARY_CONDITION_SETTER_H
