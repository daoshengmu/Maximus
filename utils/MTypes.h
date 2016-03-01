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
#import <OpenGL/gl.h>
//#import <OpenGL/gl3ext.h>
#define __OGL__
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
#else
#error Need to define other graphics api types
#endif

}

#endif  // __MTYPES_H__
