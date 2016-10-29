/*
 *  Cube.h
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __CUBE_H__
#define __CUBE_H__

#include "primitive/RenderItem.h"

namespace Maximus
{
class Cube : public RenderItem
{
public:
  Cube();
  virtual ~Cube() {}
  
private:
  static const float sCubeVertices[];
  static const uint16_t sCubeIndices[];
};
}

#endif /* __QUAD_H__ */
