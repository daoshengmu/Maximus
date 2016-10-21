/*
 *  untitled.h
 *  Maximus
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __IMGRAPHICS_H__
#define __IMGRAPHICS_H__

#include "util/MUtils.h"

namespace Maximus
{
class Surface;

enum EM_SHADERTYPE {
    St_Vertex,
    St_Fragment
};
    
class IMGraphics
{
public:
	virtual	~IMGraphics() {};
	virtual void Init() = 0;
	virtual void DrawTriangle(Surface* aSurface, const cMMatrix3Df *mvpMtx) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
  virtual void SetUniform4f(GInt index, GSizei count, const GFloat *value) = 0;
  virtual void SetUniformMatrix4f(GInt index,  GSizei count, const GFloat *value) = 0;
  virtual bool CreateShader(const char *vShader, const char *fShader, GShader* aResult) = 0;
  virtual void CreateVertexBuffer(const float* aData, int aNumVertics,
                                  int aVertexSize, GBuffer* aResult) = 0;
  virtual void CreateIndexBuffer(const uint16_t* aData, int aNumIndices,
                                 GBuffer* aResult) = 0;
  virtual void CreateVertexArrayObject(int aNumArray, GBuffer* aResult) = 0;
  virtual void SetViewport(float x, float y, float w, float h) = 0;
  virtual void Terminate() = 0;
};

}

#endif
