/*
 *  RenderItem.h
 *
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __RENDER_ITEM_H__
#define __RENDER_ITEM_H__

#include "Primitive/MObject3D.h"

namespace Maximus {
  
class Surface;
class Material;
class IMGraphics;
  
class RenderItem : public cMObject3D
{
public:
  RenderItem();
  void Init(IMGraphics* aGraphics);
  shared_ptr<Surface> GetSurface();
  
protected:
  shared_ptr<Surface> _surface;
  int _numVertices;
  int _vertexSize;
  int _numIndices;
  const float* _vertices;
  const uint16_t* _indices;
};
  
}  // End of namespace Maximus

#endif
