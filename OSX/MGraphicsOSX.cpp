//
//  MGraphicsOSX.cpp
//  Maximus
//
//  Created by User on 2/20/16.
//  Copyright 2011 Daosheng Mu. All rights reserved.
//

#include <assert.h>
#ifdef __gl_3__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif
#include "utils/MUtils.h"
#include "OSX/MGraphicsOSX.h"
#include "context/ContextOSX.h"


#define M_LOG(x) do { \
 std::cout << x << std::endl; \
} while (0)


namespace Maximus
{
    
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

// Uniform index.
enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms1[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};
    
static inline const char * GetGLErrorString(GLenum error)
{
    const char *str;
    switch( error )
    {
        case GL_NO_ERROR:
            str = "GL_NO_ERROR";
            break;
        case GL_INVALID_ENUM:
            str = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            str = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            str = "GL_INVALID_OPERATION";
            break;
#if defined __gl_h_ || defined __gl3_h_
        case GL_OUT_OF_MEMORY:
            str = "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            str = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
#endif
#if defined __gl_h_
        case GL_STACK_OVERFLOW:
            str = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            str = "GL_STACK_UNDERFLOW";
            break;
        case GL_TABLE_TOO_LARGE:
            str = "GL_TABLE_TOO_LARGE";
            break;
#endif
        default:
            str = "(ERROR: Unknown Error Enum)";
            break;
    }
    return str;
}
    
#define glError() { \
GLenum err = glGetError(); \
while (err != GL_NO_ERROR) { \
__builtin_printf("glError: %s caught at %s:%u\n", (char *)GetGLErrorString(err), __FILE__, __LINE__); \
assert(0 && "Dying..."); \
} \
}

cMGraphicsOSX::cMGraphicsOSX()
{
    
}

cMGraphicsOSX::~cMGraphicsOSX()
{
    
}

// Need to create a surface.
GLuint vertexBuffer;
GLuint indexBuffer;
// Rectangle geometry struct
int numVertics = 4;
int vertexSize = 28;
int numIndices = 6;
float *vertexData = NULL;
unsigned short *indexData = NULL;
    
void cMGraphicsOSX::Init()
{
#ifdef __MOS_OSX__
    //_context = new ContextOSX();
#else
#error "TODO: You need to new other Context for other platform..."
#endif
   // _context->Init();
    
    // Create Rect vertex / index buffer
    float vertexArray[] = {
        -0.5, 0.5, -0.5, 1, 0, 1, 1,
        -0.5, -0.5, -0.5, 0, 1, 1, 1,
        0.5, -0.5, -0.5, 1, 1, 0, 1,
        0.5, 0.5, -0.5, 1, 0, 1, 1};
    
    unsigned short indexArray[] = { 0,1,2, 2,3,0 };
    
    vertexData = (float *)malloc(vertexSize * numVertics);
    memcpy(vertexData, vertexArray, vertexSize * numVertics);
    
    indexData = (uint16 *)malloc(numIndices * sizeof(uint16));
    memcpy(indexData, indexArray, numIndices * sizeof(uint16));
    
    // Create buffer
    glError();
    glGenBuffers(1, &vertexBuffer);
    glError();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glError();
    glBufferData(GL_ARRAY_BUFFER, numVertics * vertexSize, vertexData, GL_STATIC_DRAW);
    glError();
    free(vertexData);
    
    glGenBuffers(1, &indexBuffer);
    glError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint16), indexData, GL_STATIC_DRAW);
    glError();
    free(indexData);
    
    BeginFrame();
}

GLuint vao;
int mvpUniformPos = -1;
GShader g_Shader;
    
void cMGraphicsOSX::DrawTriangle(const cMMatrix3Df *mvpMatrix, GShader shaderProgram)
{
    g_Shader = shaderProgram;
    
    // Draw rect
    glUseProgram(shaderProgram);
    glError();
    
    // Set MVP matrix
    glUniformMatrix4fv(mvpUniformPos, 1, GL_TRUE, mvpMatrix->GetItems());
    glError();
    
#ifdef __gl_3__
    // bind buffer
    glBindVertexArray(vao);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glError();
    
    //this->SetVertexDeclaration( pMaterial->GetVertexDeclaration() );
    int offset = 4 * 3;
    const GLuint vertexLoc = 0;
    const GLuint colorLoc = 1;
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, false, 4 * 7, nullptr);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, false, 4 * 7, BUFFER_OFFSET(offset));
    glEnableVertexAttribArray(colorLoc);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

void cMGraphicsOSX::BeginFrame()
{    
    glClearColor( 0.0f, 1.0f, 0.0f, 1.0f );
    glClearDepth( 1.0f );
    glClearStencil( 0 );
    
    GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    e = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    e = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
    glError();
}

void cMGraphicsOSX::EndFrame()
{
    glFlush();
    glError();
}

void cMGraphicsOSX::SetUniform4f(GInt index, GSizei count, const GFloat *value)
{
    glUniformMatrix4fv(index, count, GL_FALSE, value);
}
    
void cMGraphicsOSX::SetUniformMatrix4f(GInt index,  GSizei count, const GFloat *value)
{
    glUniformMatrix4fv(index, count, GL_FALSE, value);
}
    
GShader cMGraphicsOSX::CreateShader(const char *vShader, const char *fShader)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glError();
    glShaderSource(vertexShader, 1, &vShader, nullptr);
    glError();
    glCompileShader(vertexShader);
    glError();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShader, nullptr);
    glError();
    glCompileShader(fragmentShader);
    glError();
    
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        //The maxLength includes the NULL character
        GLchar infoLog[256];
        glGetShaderInfoLog( vertexShader, maxLength, &maxLength, infoLog );
        //We don't need the shader anymore.
        glDeleteShader(vertexShader);
        //Use the infoLog as you see fit.
        assert( 0 && infoLog );
        return NULL;
    }
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        //The maxLength includes the NULL character
        char infoLog[256];
        glGetShaderInfoLog( fragmentShader, maxLength, &maxLength, infoLog );
        
        //We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        //Use the infoLog as you see fit.
        assert( 0 && infoLog );
        return NULL;
    }
    
    GShader shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    const GLuint vertexLoc = 0;
    const GLuint colorLoc = 1;
    
    // Init attributes BEFORE linking
    glBindAttribLocation(shaderProgram, vertexLoc, "g_vPositionOS");
    glBindAttribLocation(shaderProgram, colorLoc, "g_vColorOS");
    glLinkProgram(shaderProgram);
    glError();
    
        int tt = glGetAttribLocation(shaderProgram, "g_vPositionOS");
        tt = glGetAttribLocation(shaderProgram, "g_vColorOS");
    
#ifdef __gl_3__
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
#endif
    
    // Redundant for initShader?
    int offset = 4 * 3;
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 4 * 7, 0);
    glError();
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * 7, BUFFER_OFFSET(offset));
    glError();
    // End of checking redundant
    
    const char *g_worldViewProjMatrix = "g_worldViewProjMatrix";
    mvpUniformPos = glGetUniformLocation( shaderProgram, g_worldViewProjMatrix );
    glError();
    
    // Check for link success
    GLint maxLength = 0;
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &maxLength );
    if (!maxLength)
    {
        GLchar infoLog[ 256 ];
        
        glGetProgramInfoLog( shaderProgram, maxLength, &maxLength, infoLog );
        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );
        glDeleteProgram( shaderProgram );
        return NULL;
    }
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
    glError();
    
    return shaderProgram;
}

void cMGraphicsOSX::SetViewport(float x, float y, float w, float h)
{
    glViewport(x, y, w, h);
    glError();
}
 
void cMGraphicsOSX::Terminate()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glDeleteBuffers(2, (const GLuint*) &quadID);
    glDeleteBuffers(1, (const GLuint*)&vertexBuffer);
    glDeleteBuffers(1, (const GLuint*)&indexBuffer);
    //glDeleteTextures(kNumTextures, tex);
    //glDeleteFramebuffers(kNumFBO, fbos);
    //free(resourcePath);
    glUseProgram(0);
    glDeleteProgram(g_Shader);
}

    
}
