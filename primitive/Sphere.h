/*
 *  Sphere
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "primitive/RenderItem.h"

namespace Maximus
{
class Sphere : public RenderItem
{
public:
  Sphere();
  virtual ~Sphere() {}
  
private:
  void BuildData();
  static float* GetVertexData();
  static uint16_t* GetIndexData();
  
  static bool mInitData;
  static const float sRadius;
  static const uint32_t sLatitude;
  static const uint32_t sLongitude;
  static const uint32_t sSphereNumIndices;
  static const uint32_t sSphereNumVertices;
};
}

#endif /* __SPHERE_H__ */
