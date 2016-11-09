//
//  MRenderOSX.h
//  MaximusOSX
//
//  Created by Daosheng Mu on 2/19/16.
//
//  The 3D coordinate is Y-up right hand coordinate.
//

#ifndef MRender_h
#define MRender_h

#include "util/MUtils.h"

namespace Maximus
{

class IMGraphics;
class cMCamera;
class RenderItem;
class Surface;

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
public:
  void Init(int width, int height);
  void Update();
  void Draw();
  void SetViewport(int x, int y, int w, int h);
  void Terminate();
  void SetCamera(cMCamera *aCamera);
  cMCamera* GetCamera();
  void AddRenderItem(RenderItem* aRenderItem);
  
  static cMRender& GetInstance();
  
private:
  cMRender();
  ~cMRender();
  
  cMRender(const cMRender& rValue);
  cMRender& operator = (const cMRender& rValue);
  
  static bool _bInit;
  IMGraphics* _graphics;
  cMCamera*   _camera;
  cMMatrix3Df _mvpMatrix;
  Rect       _viewport;
  vector<RenderItem> mItems;
};

}

#endif /* MRender_h */
