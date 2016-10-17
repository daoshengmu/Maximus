/*
 *  MTypes.h
 *  Maximus
 *
 *  Created by User on 5/29/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MTYPES_H__
#define __MTYPES_H__

#ifdef __MOS_OSX__
#define __OGL__
#define __gl_3__

#ifdef __gl_3__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <OpenGL/gl.h>
#endif
#elif

#error Need to define other graphics api types
#endif

namespace Maximus
{

#ifdef __OGL__
    typedef GLint   GInt;
    typedef GLsizei GSizei;
    typedef GLboolean GBool;
    typedef GLfloat GFloat;
    typedef GLuint GShader;
    typedef GLuint GBuffer;
#else
#error Need to define other graphics api types
#endif

}

#endif  // __MTYPES_H__
