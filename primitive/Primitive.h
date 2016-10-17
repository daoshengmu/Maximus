/*
 *  Primitive.h
 *
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MOBJECT3D_H__
#define __MOBJECT3D_H__

#include "Primitive/MObject3D.h"

namespace Maximus {
    
class Primitive : public CMObject3D
{
private:
    Material* _material;
    
    float* _vertices;
    unsigned short* _indices;
    int _numVertics = 4;
    int _vertexSize = 28;
    int _numIndices = 6;
    
    GBuffer _vertexBuffer;
    GBuffer _indexBuffer;

public:
    Primitive();
  
    virtual ~Primitive();
};
}

#endif
