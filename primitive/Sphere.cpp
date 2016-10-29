/*
 *  Sphere.cpp
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */
#include "primitive/Sphere.h"

namespace Maximus {

struct Vertex
{
  float x, y, z;
  //uint32 color;
  float r, g, b, a;
  //  float u, v;
  //  float normalX, normalY, normalZ;
  //  float tangentX, tangentY, tangentZ;
  //  float binormalX, binormalY, binormalZ;
};
  
const float Sphere::sRadius = 0.5f;
const uint32_t Sphere::sLatitude = 30;
const uint32_t Sphere::sLongitude = 30;
bool Sphere::mInitData = false;
const uint32_t Sphere::sSphereNumIndices = (sLatitude - 2) * sLongitude * 2 * 3;
const uint32_t Sphere::sSphereNumVertices = (sLatitude - 2) * (sLongitude + 1) + 2;
  
Sphere::Sphere()
{
  _numVertices = sSphereNumVertices;
  _vertexSize = sizeof(Vertex);
  _numIndices = sSphereNumIndices;
 
  if (!mInitData) {
    BuildData();
    mInitData = true;
  }
  
  _vertices = GetVertexData();
  _indices = GetIndexData();
}
  
void Sphere::BuildData()
{
  Vertex vertices[sLatitude * sLongitude];
  
  uint32_t r,s;
  float x,y,z;
  int index = 0;
  float theta;
  float phi;
  
  for ( r = 1; r < sLatitude -1; r++ )
  {
    for ( s = 0; s < sLongitude + 1; s++, ++index )
    {
      theta = (float)r / (float)(sLatitude - 1) * M_M_PI;
      phi = (float)s / (float)(sLongitude) * M_M_PI * 2;
      
      x = sin(theta) * cos(phi);
      y = cos(theta);
      z = -sin(theta) * sin(phi);
      
      vertices[index].x = x * sRadius;
      vertices[index].y = y * sRadius;
      vertices[index].z = z * sRadius;

//      _sphereVertices[index].normalX = x;
//      _sphereVertices[index].normalY = y;
//      _sphereVertices[index].normalZ = z;
      
//      _sphereVertices[index].u = 1.0f - (float)s / (float)sLongitude;
//      _sphereVertices[index].v = (float)r / (float)( sLatitude - 1 );
      
      vertices[index].r = 1.0f;
      vertices[index].g = 1.0f;
      vertices[index].b = 1.0f;
      vertices[index].a = 1.0f;
    }
  }
  
  // top pos
  vertices[index].x = 0 * sRadius;
  vertices[index].y = 1 * sRadius;
  vertices[index].z = 0 * sRadius;
  // color
  vertices[index].r = 1.0f;
  vertices[index].g = 1.0f;
  vertices[index].b = 1.0f;
  vertices[index].a = 1.0f;
  ++index;

  // bottom pos
  vertices[index].x = 0 * sRadius;
  vertices[index].y = -1 * sRadius;
  vertices[index].z = 0 * sRadius;
  // color
  vertices[index].r = 1.0f;
  vertices[index].g = 1.0f;
  vertices[index].b = 1.0f;
  vertices[index].a = 1.0f;
  ++index;
  
  float* pVertexData = GetVertexData();
  memcpy(pVertexData, vertices, _numVertices * _vertexSize);

  uint16_t* pIndexData = GetIndexData();
  int slice = sLongitude + 1;
  uint32_t c = 0, j = 0;
  
  for ( c = 0, j = 0; j < sLatitude - 3; ++j )
  {
    for ( int i = 0; i < slice - 1; ++i )
    {
      pIndexData[c++] = uint16_t(j * slice + i);
      pIndexData[c++] = uint16_t((j+1) * slice + i +1);
      pIndexData[c++] = uint16_t( j * slice + i + 1);
      
      pIndexData[c++] = uint16_t(j * slice + i);
      pIndexData[c++] = uint16_t((j+1) * slice + i);
      pIndexData[c++] = uint16_t((j+1) * slice + i + 1);
    }
    
  }
  
  for ( int i = 0; i < slice - 1; ++i )
  {
    pIndexData[c++] = uint16_t((sLatitude - 2) * slice);
    pIndexData[c++] = uint16_t(i);
    pIndexData[c++] = uint16_t(i + 1);
    
    pIndexData[c++] = uint16_t((sLatitude - 2) * slice + 1);
    pIndexData[c++] = uint16_t((sLatitude - 3) * slice + i + 1);
    pIndexData[c++] = uint16_t((sLatitude - 3) * slice + i);
  }
  // End of generating indices
}

/* static */
float* Sphere::GetVertexData()
{
  static float sphereVertices[sLatitude * sLongitude *
                              (sizeof(Vertex) / sizeof(float))];
  
  return sphereVertices;
}

/* static */
uint16_t* Sphere::GetIndexData()
{
  static uint16_t sphereIndices[sSphereNumIndices];

  return sphereIndices;
}
  
} // End of namespace Maximus
