/*
 *  Quad.cpp
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */
#include "primitive/Quad.h"

namespace Maximus {

const float Quad::_quadVertices[] = {
  -0.5, 0.5, -0.5, 1, 0, 1, 1,
  -0.5, -0.5, -0.5, 0, 1, 1, 1,
  0.5, -0.5, -0.5, 1, 1, 0, 1,
  0.5, 0.5, -0.5, 1, 0, 1, 1
};
  
const uint16_t Quad::_quadIndices[] = { 0,1,2, 2,3,0 };
  
Quad::Quad()
{
  _numVertices = 4;
  _vertexSize = 28;
  _numIndices = 6;
  
  _vertices = Quad::_quadVertices;
  _indices = Quad::_quadIndices;
}

} // End of namespace Maximus
