/*
 *  Quad.h
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __QUAD_H__
#define __QUAD_H__

#include "primitive/RenderItem.h"

namespace Maximus
{
class Quad : public RenderItem
{
public:
  Quad();
  virtual ~Quad() {}
  
private:
  static const float _quadVertices[];
  static const uint16_t _quadIndices[];
  
//  int _numVertics;
//  int _vertexSize;
//  int _numIndices;
};
}

#endif /* __QUAD_H__ */
