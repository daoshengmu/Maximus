//
//  MRenderOSX.cpp
//  MaximusOSX
//
//  Created by Daosheng Mu on 2/19/16.
//
//

#include "MRender.h"
#include "utils/MMath.h"
#include "OSX/MGraphicsOSX.h"
#include "camera/MCamera.h"
#include "BasicShader.h"

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
    
//    // Init MVP matrix
//    float l, r, b, t;
//    float far = 1000.0f, near = 1.0f;
//    
//    l = (float)-width / 2;
//    r = (float)width / 2;
//    b = (float)-height / 2;
//    t = (float)height / 2;
//    
//    cMMatrix3D<float> projMtx(
//                              2.0f/(r-l)  , 0.0f         , 0.0f                 , 0.0f,
//                              0.0f	      , 2.0f/(t-b)   , 0.0f                 , 0.0f,
//                              0.0f        , 0.0f         , -2.0f/(far - near)    , 0.0f,
//                              -(l+r)/(r-l), -(t+b)/(t-b) , -(far+near)/(far-near)     , 1.0f );  // orthogonal matrix
//    
//    
//    float fov_x = 90.0f;
//    float fov_y = 73.74f;
//    float Q;
//    
//    fov_x =  M_DEGREE_TO_RADIAN( fov_x );
//    fov_y =  M_DEGREE_TO_RADIAN( fov_y );
//    Q     =  far / (far - near);
    
    // Init shader
    BasicShader shader;
    shaderProgram = _graphics->CreateShader(shader.GetVertexShader()->c_str(), shader.GetFragmentShader()->c_str());
}

void cMRender::SetCamera(cMCamera *pCamera)
{
    _camera = pCamera;
}

void cMRender::SetViewport(int x, int y, int w, int h)
{
    _viewport.Set(x, y, w, h);
    _graphics->SetViewport(x, y, w, h);
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
    
    modelMtx.scale(cMVector3D<float>(1000,1000,1000));
    modelMtx.translate( 0, 0, -20 );
    
//    _mvpMatrix = modelMtx;
//    _mvpMatrix *= vpMtx;

    _mvpMatrix = modelMtx;
    _mvpMatrix *= *viewMtx;
    _mvpMatrix *= *projMtx;

    _graphics->DrawTriangle(&_mvpMatrix, shaderProgram);
    // End of draw
    
    _graphics->EndFrame();
}

void cMRender::Terminate()
{
    _graphics->Terminate();
}

}
