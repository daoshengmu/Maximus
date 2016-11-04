/*
 *  Primitive.h
 *
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __SURFACE_H__
#define __SURFACE_H__


namespace Maximus {
  
class IMGraphics;

class Surface
{
public:
  Surface();
  explicit Surface(const Surface& rValue)
  {
    _numVertics = rValue._numVertics;
    _numIndices = rValue._numIndices;
    _vertexSize = rValue._vertexSize;
    _material = rValue._material;
    _vertices = rValue._vertices;
    _indices = rValue._indices;
    _vertexBuffer = rValue._vertexBuffer;
    _indexBuffer = rValue._indexBuffer;
    _vertexArrayObject = rValue._vertexArrayObject;
  }
  
  virtual ~Surface();

//  Primitive& operator = (const Primitive& rValue);

  void Init(IMGraphics* aGraphics, int aNumVertics, int aVertexSize,
            int aNumIndices, const float* aVertices, const uint16_t* aIndices,
            shared_ptr<cMMatrix3Df> aWorldMtx);
  int GetNumVertices();
  int GetVertexSize();
  int GetNumIndices();
  shared_ptr<cMMatrix3Df> GetWorldMatrix();
  shared_ptr<Material> GetMaterial();
  
protected:
  // Get from RenderItem
  int _numVertics;
  int _vertexSize;
  int _numIndices;
  const float* _vertices;
  const uint16_t* _indices;
  
  shared_ptr<cMMatrix3Df> _worldMtx;
  
  GBuffer _vertexArrayObject;
  GBuffer _vertexBuffer;
  GBuffer _indexBuffer;

private:
  GBuffer GetVertexArrayObject();
  GBuffer GetVertexBuffer();
  GBuffer GetIndexBuffer();

  // TODO: Material needs to be created by MRender
  // and set to primitive.
  shared_ptr<Material> _material;

  friend class cMGraphicsOSX;
};
}  // End of namespace Maximus

#endif
