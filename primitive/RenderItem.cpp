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
#include "material/Material.h"

namespace Maximus
{

RenderItem::RenderItem()
  : _numVertices(0), _numIndices(0), _vertexSize(0),
    _vertices(nullptr), _indices(nullptr)
{
  
}

void RenderItem::Init(IMGraphics* aGraphics)
{
  assert(!_surface); // To make sure this RenderItem be created only once.
  
  _surface = make_shared<Surface>();
  _surface->Init(aGraphics, _numVertices, _vertexSize,
                 _numIndices, _vertices, _indices, mWorldMtx);
}
  
shared_ptr<Surface> RenderItem::GetSurface()
{
  return _surface;
}

void RenderItem::SetMaterialColor(const cMVector4Df& aColor)
{
  _surface->GetMaterial()->SetMaterialColor(aColor);
}
  
}  // End of namespace Maximus
