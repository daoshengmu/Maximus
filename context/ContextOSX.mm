/*
 *  MaxiFactory.cpp
 *  Maximus
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "context/ContextOSX.h"

namespace Maximus
{
    
bool ContextOSX::Init()
{
#ifdef __gl_3__
    NSOpenGLPixelFormatAttribute attrs[] = {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core, //Core Profile
        0
    };
#else
    NSOpenGLPixelFormatAttribute attrs[] = {
        kCGLPFAAccelerated,
        kCGLPFANoRecovery,
        kCGLPFADoubleBuffer,
        kCGLPFAColorSize, 24,
        kCGLPFADepthSize, 16,
        0
    };
#endif
    
    //cbCtx = (CallbackContext*) malloc(sizeof(CallbackContext));
    
   // NSOpenGLPixelFormat* pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs]autorelease];
    
    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc]
                                        initWithAttributes:attrs];
    if (!pixelFormat) {
        printf("Failed to create NSOpenGLPixelFormat.");
        return false;
    }
    
    NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat
                                                          shareContext:nullptr];
    
    [pixelFormat release];
    
    _context = context;
    [_context makeCurrentContext];
    
    printf("Vendor:   %s\n", glGetString(GL_VENDOR)                  );
    printf("Renderer: %s\n", glGetString(GL_RENDERER)                );
    printf("Version:  %s\n", glGetString(GL_VERSION)                 );
    printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    return true;
}
    
void* ContextOSX::GetContext()
{
    return _context;
}

void ContextOSX::Terminate()
{
    [_context release];
}

}