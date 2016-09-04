/*
 *  ContextOSX.h
 *  Maximus
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __CONTEXT_OSX_H__
#define __CONTEXT_OSX_H__

#include "context/Context.h"

#include <OpenGL/gl.h>

#ifdef __OBJC__
#include <AppKit/NSOpenGL.h>
#else
typedef void NSOpenGLContext;
#endif

namespace Maximus
{
    
//typedef struct _CallbackContext
//{
//    NSOpenGLContext* ctx;
//  //  cMRender* maxiRenderer;
//} CallbackContext;

//@interface GLView : NSOpenGLView {
//    CallbackContext* cbCtx;
//    NSOpenGLPixelFormat* pf;
//    CVDisplayLinkRef displayLink;
//}

class ContextOSX: public Context
{
public:
    virtual bool Init() override;
    virtual void Terminate() override;
    virtual void* GetContext() override;
    
private:
//    GLView glView;
    NSOpenGLContext* _context;
};
    
}

#endif /* __CONTEXT_OSX_H__ */