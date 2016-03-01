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
}

cMRender::~cMRender()
{
    if (_graphics)
    {
        delete _graphics;
        _graphics = nullptr;
    }
}
    
GShader shaderProgram = -1;

void cMRender::Init(int width, int height)
{
    _graphics->Init();
    
    // Init MVP matrix
    float l, r, b, t;
    float far = 1000.0f, near = 1.0f;
    
    l = (float)-width / 2;
    r = (float)width / 2;
    b = (float)-height / 2;
    t = (float)height / 2;
    
    // Ortho has bug?
    cMMatrix3D<float> projMtx(
                              2.0f/(r-l)  , 0.0f         , 0.0f                 , 0.0f,
                              0.0f	      , 2.0f/(t-b)   , 0.0f                 , 0.0f,
                              0.0f        , 0.0f         , -2.0f/(far - near)    , 0.0f,
                              -(l+r)/(r-l), -(t+b)/(t-b) , -(far+near)/(far-near)     , 1.0f );  // orthogonal matrix
    
    
    float fov_x = 90.0f;
    float fov_y = 73.74f;
    float Q;
    
    fov_x =  M_DEGREE_TO_RADIAN( fov_x );
    fov_y =  M_DEGREE_TO_RADIAN( fov_y );
    Q     =  far / (far - near);
    
    
    
    //    cMMatrix3D<float> projMtx(
    //                               1.0f/tan(fov_x*0.5f), 0.0f                , 0.0f          , 0.0f,
    //                               0.0f                , 1.0f/tan(fov_y*0.5f), 0.0f          , 0.0f,
    //                               0.0f                , 0.0f                , Q             , 1.0f,
    //                               0.0f                , 0.0f                , (-near * Q) , 0.0f );
    //
    cMMatrix3D<float> modelMtx;
    cMMatrix3D<float> viewMtx;
    
    modelMtx.scale(cMVector3D<float>(1000,1000,1000));
    modelMtx.translate( 0, 0, -20 );
    
    //viewMtx.translate( 0, 0, -1.5 );
    //   cMVector3D<float> origin( 0, 0, -1.5 );
    //   origin *= -1;
    //    const float *raws = viewMtx.GetItems();
    
    //    viewMtx.SetItems(
    //        raws[0], raws[8],  raws[4], 0.0,
    //        raws[1], raws[9],  raws[5], 0.0,
    //        raws[2], raws[10],  raws[6], 0.0,
    //        origin.x, origin.y,  origin.z, 1.0
    //    );
    
    _mvpMatrix = modelMtx;
    _mvpMatrix *= viewMtx;
    _mvpMatrix *= projMtx;
    
    // Init shader
    BasicShader shader;
    shaderProgram = _graphics->CreateShader(shader.GetVertexShader()->c_str(), shader.GetFragmentShader()->c_str());
    
//        glUniformMatrix4fv( mvpUniformPos, 1, GL_TRUE, mvpMatrix.GetItems() );
//    _graphics->SetUniformMatrix4f(0, 1, _mvpMatrix.GetItems());
//    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
//    CheckForErrors();
//    
//    BasicShader shader;
//    const char* shaderData = shader.GetVertexShader()->c_str();
//    glShaderSource( vertexShader, 1, &shaderData, NULL );
//    CheckForErrors();
//    glCompileShader( vertexShader );
//    CheckForErrors();
//    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
//    shaderData = shader.GetFragmentShader()->c_str();
//    glShaderSource( fragmentShader, 1, &shaderData, NULL );
//    CheckForErrors();
//    glCompileShader( fragmentShader );
//    CheckForErrors();
//    
//    GLint isCompiled = 0;
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
//    if(isCompiled == GL_FALSE)
//    {
//        GLint maxLength = 0;
//        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
//        //The maxLength includes the NULL character
//        GLchar infoLog[256];
//        glGetShaderInfoLog( vertexShader, maxLength, &maxLength, infoLog );
//        //We don't need the shader anymore.
//        glDeleteShader(vertexShader);
//        //Use the infoLog as you see fit.
//        assert( 0 && "ContextOGL:: Create vertex shader error" );
//        return NULL;
//    }
//    
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
//    if(isCompiled == GL_FALSE)
//    {
//        GLint maxLength = 0;
//        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
//        //The maxLength includes the NULL character
//        char infoLog[256];
//        glGetShaderInfoLog( fragmentShader, maxLength, &maxLength, infoLog );
//        
//        //We don't need the shader anymore.
//        glDeleteShader(fragmentShader);
//        //Use the infoLog as you see fit.
//        assert( 0 && "ContextOGL:: Create fragment shader error" );
//        return NULL;
//    }
//    
//    program = glCreateProgram();
//    glAttachShader( program, vertexShader );
//    glAttachShader( program, fragmentShader );
//    const GLuint vertexLoc = 0;
//    const GLuint colorLoc = 1;
//    
//    // Init attributes BEFORE linking
//    glBindAttribLocation(program, vertexLoc, "g_vPositionOS");
//    glBindAttribLocation(program, colorLoc, "g_vColorOS");
//    glLinkProgram( program );
//    CheckForErrors();
//    
//    //    int tt = glGetAttribLocation(program, "g_vPositionOS");
//    //    tt = glGetAttribLocation(program, "g_vColorOS");
//    
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    
//    int offset = 4 * 3;
//    glEnableVertexAttribArray( vertexLoc );
//    glVertexAttribPointer( vertexLoc, 3, GL_FLOAT, GL_FALSE, 4 * 7, 0 );
//    CheckForErrors();
//    glEnableVertexAttribArray( colorLoc );
//    glVertexAttribPointer( colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * 7, &offset );
//    CheckForErrors();
//    
//    const char *g_worldViewProjMatrix = "g_worldViewProjMatrix";
//    mvpUniformPos = glGetUniformLocation( program, g_worldViewProjMatrix );
//    CheckForErrors();
//    
//    // Check for link success
//    GLint maxLength = 0;
//    glGetProgramiv( program, GL_LINK_STATUS, &maxLength );
//    if (!maxLength)
//    {
//        GLchar infoLog[ 256 ];
//        
//        glGetProgramInfoLog( program, maxLength, &maxLength, infoLog );
//        glDeleteShader( vertexShader );
//        glDeleteShader( fragmentShader );
//        glDeleteProgram( program );
//        return NULL;
//    }
//    glDeleteShader( vertexShader );
//    glDeleteShader( fragmentShader );
}

void cMRender::SetCamera(cMCamera *pCamera)
{
//    _graphics->SetUniformMatrix4f(<#GInt index#>, <#GSizei count#>, <#const GFloat *value#>);
}

void cMRender::SetViewport(int x, int y, int w, int h)
{
    _viewport.Set(x, y, w, h);
    _graphics->SetViewport(x, y, w, h);
    // XXX TODO reset the projection matrix
}

void cMRender::Draw()
{
    _graphics->BeginFrame();
    _graphics->DrawTriangle(&_mvpMatrix, shaderProgram);
    _graphics->EndFrame();
}

void cMRender::Terminate()
{
    _graphics->Terminate();
}

}
