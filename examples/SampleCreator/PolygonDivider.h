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

#ifndef POLYGON_DIVIDER_H
#define POLYGON_DIVIDER_H

#include <string>
#include <vector>
#include <algorithm> // for max, min
#include "Vec3.h"
#include "BCMPolylib.h"

#include "BCMTools.h"
#include "MultiRootDivider.h"
#include "BoundingBox.h"

using namespace Vec3class;

class PolygonDivider : public MultiRootDivider {

  int minLevel;

  const PolylibNS::BCMPolylib* pl;

  const std::vector<PolygonGroupSpec>& polygonGroupList;

  const std::vector<BoundingBoxSpec>& boundingBoxList;

  double marginRatio;

public:

  PolygonDivider(const Vec3d& origin, double rootLength, const RootGrid* rootGrid,
                 int minLevel, const PolylibNS::BCMPolylib* pl,
                 const std::vector<PolygonGroupSpec>& polygonGroupList,
                 const std::vector<BoundingBoxSpec>& boundingBoxList,
                 double marginRatio = 0.0)
    : MultiRootDivider(origin, rootLength, rootGrid),
      minLevel(minLevel), pl(pl),
      polygonGroupList(polygonGroupList), boundingBoxList(boundingBoxList),
      marginRatio(marginRatio) {
  }

  ~PolygonDivider() {}

  NodeType operator() (const Pedigree& pedigree) {

    int level = pedigree.getLevel();

    if  (level < minLevel) return BRANCH;

    NodeType ret = LEAF_ACTIVE;

    for (std::vector<BoundingBoxSpec>::const_iterator it = boundingBoxList.begin();
         it != boundingBoxList.end(); ++it) {
      int maxLevel = it->level;
      if (level < maxLevel) {
        BoundingBox box = it->boundingBox;
        BoundingBox region = defineSearchRegion(pedigree, maxLevel);
        region.setMargin(marginRatio / (1 << maxLevel));
        if (box.intersects(region)) ret = BRANCH;
      }
    }


    for (std::vector<PolygonGroupSpec>::const_iterator it = polygonGroupList.begin();
         it != polygonGroupList.end(); ++it) {
      int maxLevel = it->level;
      if (level < maxLevel) {
        const std::string& polygonGroup = it->polygonGroupName;
        BoundingBox region = defineSearchRegion(pedigree, maxLevel);
        region.setMargin(marginRatio / (1 << maxLevel));
        Vec3class::Vec3f min(region.getMin().x, region.getMin().y, region.getMin().z);
        Vec3class::Vec3f max(region.getMax().x, region.getMax().y, region.getMax().z);
        std::vector<PolylibNS::Triangle*>* polygonList
                        = pl->search_polygons(polygonGroup, min, max, false);
        int nPolygon = polygonList->size();
        delete polygonList;
        if (nPolygon > 0) ret = BRANCH;
      }
    }

    return ret;
  }

};

#endif // POLYGON_DIVIDER_H
