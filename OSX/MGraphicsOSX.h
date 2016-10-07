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
    virtual void DrawTriangle(const cMMatrix3Df *mvpMtx, GShader shaderProgram);
    virtual void BeginFrame();
    virtual void EndFrame();
    virtual void SetUniform4f(GInt index, GSizei count, const GFloat *value);
    virtual void SetUniformMatrix4f(GInt index,  GSizei count, const GFloat *value);
    virtual GShader CreateShader(const char *vShader, const char *fShader);
    virtual void SetViewport(float x, float y, float w, float h) ;
    virtual void Terminate();
    
private:
    Context*    _context;
};

}

#endif /* MGraphicsOSX_h */

