/*
 *  RenderItem.cpp
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "primitive/RenderItem.h"
#include "primitive/Surface.h"

namespace Maximus
{

RenderItem::RenderItem()
  : _numVertics(0), _numIndices(0), _vertexSize(0),
    _vertices(nullptr), _indices(nullptr)
{
  
}

void RenderItem::Init(IMGraphics* aGraphics)
{
  _surface = make_shared<Surface>();
  _surface->Init(aGraphics, _numVertics, _vertexSize,
                 _numIndices, _vertices, _indices);
}
  
shared_ptr<Surface> RenderItem::GetSurface()
{
  return _surface;
}

}  // End of namespace Maximus
