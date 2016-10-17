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
#include "shader/BasicShader.h"

namespace Maximus {
    
cMRender::cMRender()
{
#ifdef __MOS_OSX__
    _graphics = new cMGraphicsOSX();
#else
    #error undefine other type for cMGraphics
#endif
    _camera = new cMCamera();
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
    
GShader shaderProgram = -1;

void cMRender::Init(int width, int height)
{
    _graphics->Init();
    _camera->SetViewPort(width, height);
    
    // Init shader
    BasicShader shader;
    shaderProgram = _graphics->CreateShader(shader.GetVertexShader()->c_str(), shader.GetFragmentShader()->c_str());
}

void cMRender::SetCamera(cMCamera *pCamera)
{
    _camera = pCamera;
}
    
cMCamera* cMRender::GetCamera()
{
    return _camera;
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
    _camera->Update();
    _graphics->BeginFrame();
    
    const cMMatrix3Df* viewMtx = _camera->GetViewMatrix();
    const cMMatrix3Df* projMtx = _camera->GetProjMatrix();
    
    cMMatrix3Df vpMtx(*viewMtx);
    vpMtx *= *projMtx;
    
    
    // For loop draw list
    cMMatrix3D<float> modelMtx;
//    
//    modelMtx.scale(cMVector3D<float>(1000,1000,1000));
    modelMtx.scale(cMVector3D<float>(10,10,1));
    modelMtx.translate(0, 0, 20);

    _mvpMatrix = modelMtx;
    _mvpMatrix *= vpMtx;

    _graphics->DrawTriangle(&_mvpMatrix, shaderProgram);
    // End of draw
    
    _graphics->EndFrame();
}

void cMRender::Terminate()
{
    _graphics->Terminate();
}

}
