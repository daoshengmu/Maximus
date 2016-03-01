//
//  MRenderOSX.h
//  MaximusOSX
//
//  Created by Daosheng Mu on 2/19/16.
//
//

#ifndef MRender_h
#define MRender_h

#include "utils/MUtils.h"

namespace Maximus
{

class IMGraphics;
class cMCamera;

struct Rect
{
    float x, y, w, h;
    
    void Set(float inX, float inY, float inW, float inH)
    {
        x = inX, y = inY, w = inW, h = inH;
    }
};

class cMRender
{
private:
    IMGraphics* _graphics;
    cMCamera*   _camera;
    cMMatrix3Df _mvpMatrix;
    Rect       _viewport;
    
public:
    cMRender();
    ~cMRender();
    
    void Init(int width, int height);
    void Draw();
    void SetViewport(int x, int y, int w, int h);
    void Terminate();
    void SetCamera(cMCamera *pCamera);
};

}

#endif /* MRender_h */
