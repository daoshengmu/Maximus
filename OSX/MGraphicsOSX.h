//
//  MGraphicsOSX.h
//  MaximusOSX
//
//  Created by Daosheng Mu on 2/19/16.
//
//

#ifndef MGraphicsOSX_h
#define MGraphicsOSX_h

#include "interface/IMGraphics.h"
#include "util/MUtils.h"
//#include <OpenGL/glu.h>

namespace Maximus
{

class Context;
    
class cMGraphicsOSX : public IMGraphics
{
public:
  cMGraphicsOSX();
  ~cMGraphicsOSX();
  
  virtual void Init();
  virtual void DrawTriangle(Surface* aSurface, const cMMatrix3Df *mvpMtx);
  virtual void BeginFrame();
  virtual void EndFrame();
  virtual void SetUniform4f(GInt index, GSizei count, const GFloat *value);
  virtual void SetUniformMatrix4f(GInt index,  GSizei count, const GFloat *value);
  virtual bool CreateShader(const char *vShader, const char *fShader, GShader* aResult);
  virtual void SetViewport(float x, float y, float w, float h) ;
  virtual void CreateVertexBuffer(const float* aData, int aNumVertics,
                                  int aVertexSize, GBuffer* aResult);
  virtual void CreateIndexBuffer(const uint16_t* aData, int aNumIndices,
                                 GBuffer* aResult);
  virtual void CreateVertexArrayObject(int aNumArray, GBuffer* aResult);
  virtual void Terminate();
  
  static void ErrorCheck();
    
private:
  Context*    _context;

};

}

#endif /* MGraphicsOSX_h */

