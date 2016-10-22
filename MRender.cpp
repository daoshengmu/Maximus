//
//  MRenderOSX.cpp
//  MaximusOSX
//
//  Created by Daosheng Mu on 2/19/16.
//
//

#include "MRender.h"
#include "util/MMath.h"
#include "OSX/MGraphicsOSX.h"
#include "camera/MCamera.h"
#include "primitive/RenderItem.h"
#include "primitive/Surface.h"

namespace Maximus
{

bool cMRender::_bInit = false;
  
cMRender::cMRender()
{
  assert(!_bInit &&
         "Get cMRender via cMRender::GetInstance.");

#ifdef __MOS_OSX__
  _graphics = new cMGraphicsOSX();
#else
  #error undefine other type for cMGraphics
#endif
  _camera = new cMCamera();
  _bInit = true;
}

cMRender::~cMRender()
{
  if (_graphics)
  {
      delete _graphics;
      _graphics = nullptr;
  }
  
  if (_camera)
  {
      delete _camera;
      _camera = nullptr;
  }
}

void cMRender::Init(int width, int height)
{
  _graphics->Init();
  _camera->SetViewPort(width, height);
}

/* static */
cMRender& cMRender::GetInstance()
{
  static cMRender renderer;

  return renderer;
}
  
void cMRender::SetCamera(cMCamera *aCamera)
{
  _camera = aCamera;
}
  
cMCamera* cMRender::GetCamera()
{
  return _camera;
}

void cMRender::AddRenderItem(RenderItem* aRenderItem)
{
  // Init primitives
  aRenderItem->Init(_graphics);
  aRenderItem->Update();
  shared_ptr<Surface> surf = aRenderItem->GetSurface();

  _surfaces.push_back(surf);
}
  
void cMRender::SetViewport(int x, int y, int w, int h)
{
  _viewport.Set(x, y, w, h);
  _graphics->SetViewport(x, y, w, h);
  _camera->SetViewPort(w, h);
  // XXX TODO reset the projection matrix
}

void cMRender::Draw()
{
  // TODO: put to cMRender::Update();
  _camera->Update();

  _graphics->BeginFrame();
  
  const cMMatrix3Df* viewMtx = _camera->GetViewMatrix();
  const cMMatrix3Df* projMtx = _camera->GetProjMatrix();
  
  cMMatrix3Df vpMtx(*viewMtx);
  vpMtx *= *projMtx;
  
  for (uint i = 0; i < _surfaces.size(); ++i) {
    shared_ptr<cMMatrix3Df> modelMtx = _surfaces[i]->GetWorldMatrix();
    
    _mvpMatrix = *modelMtx;
    _mvpMatrix *= vpMtx;
    
    _graphics->DrawTriangle(_surfaces[i].get(), &_mvpMatrix);
    // End of draw
  }
  _graphics->EndFrame();
}

void cMRender::Terminate()
{
  _graphics->Terminate();
}

}
