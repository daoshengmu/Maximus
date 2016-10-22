/*
 *  Primitive.cpp
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "interface/IMGraphics.h"
#include "material/DefaultMaterial.h"
#include "primitive/Surface.h"

namespace Maximus
{

Surface::Surface()
  : _material(nullptr), _vertices(nullptr),
    _indices(nullptr), _numVertics(0), _vertexSize(0),
    _numIndices(0), _vertexArrayObject(0), _vertexBuffer(0),
    _indexBuffer(0)
{
}

Surface::~Surface()
{
  _material = nullptr;
  
  // TODO: these should be moved to MGraphicsOSX for releasing
  // GL resource.
  glDeleteBuffers(1, &_vertexBuffer);
  glDeleteBuffers(1, &_indexBuffer);
  glDeleteVertexArrays(1, &_vertexArrayObject);
}

//Primitive& Primitive::operator=(const Primitive& rValue)
//{
//  int tet;
//  return *this;
//}
  
void Surface::Init(IMGraphics* aGraphics, int aNumVertics, int aVertexSize,
                   int aNumIndices, const float* aVertices, const uint16_t* aIndices,
                   shared_ptr<cMMatrix3Df> aWorldMtx)
{
  _numVertics = aNumVertics;
  _vertexSize = aVertexSize;
  _numIndices = aNumIndices;
  _vertices = aVertices;
  _indices = aIndices;
  _worldMtx = aWorldMtx;
  
  // Create vertex / index buffer
  aGraphics->CreateVertexArrayObject(1, &_vertexArrayObject);
  aGraphics->CreateVertexBuffer(_vertices, _numVertics, _vertexSize, &_vertexBuffer);
  aGraphics->CreateIndexBuffer(_indices, _numIndices, &_indexBuffer);
  
  // Create material
  _material = make_shared<DefaultMaterial>();
  _material->CreateShader(aGraphics);
}
  
shared_ptr<Material> Surface::GetMaterial()
{
  return _material;
}
  
GBuffer Surface::GetVertexArrayObject()
{
  return _vertexArrayObject;
}
  
GBuffer Surface::GetVertexBuffer()
{
  return _vertexBuffer;
}

GBuffer Surface::GetIndexBuffer()
{
  return _indexBuffer;
}
  
int Surface::GetNumIndices()
{
  return _numIndices;
}

int Surface::GetNumVertices()
{
  return _numVertics;
}
 
shared_ptr<cMMatrix3Df> Surface::GetWorldMatrix()
{
  return _worldMtx;
}

}  // End of namespace Maximus
