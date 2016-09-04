/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The OpenGL view. It delegates to the renderer class for drawing.
 */


//#import <Cocoa/Cocoa.h>
//#import <QuartzCore/QuartzCore.h>
#include "MRender.h"

using namespace Maximus;

//class OpenGLRenderer;

typedef struct _CallbackContext
{
	NSOpenGLContext* ctx;
    cMRender* maxiRenderer;
} CallbackContext;

@interface GLView : NSOpenGLView {
	CallbackContext* cbCtx;
	NSOpenGLPixelFormat* pf;
	CVDisplayLinkRef displayLink;
}

@end
