/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The OpenGL view. It delegates to the renderer class for drawing.
 */


#import "GLView.h"
#include "factory/MaxiFactory.h"
#include "camera/MCamera.h"
#include "primitive/Quad.h"
#include "primitive/Cube.h"
#include "primitive/Sphere.h"

#define k1KeyCode 18
#define k2KeyCode 19
#define k3KeyCode 20
#define k4KeyCode 21
#define kSpacebarKeyCode 49

using namespace Maximus;

static CVReturn Heartbeat(CVDisplayLinkRef displayLink,
                          const CVTimeStamp *inNow,
                          const CVTimeStamp *inOutputTime,
                          CVOptionFlags flagsIn,
                          CVOptionFlags *flagsOut,
                          void *displayLinkContext )
{
  CallbackContext* ctx = (CallbackContext*) displayLinkContext;
	CGLSetCurrentContext((CGLContextObj) [ctx->ctx CGLContextObj]);
  ctx->maxiRenderer->Draw();
	CGLFlushDrawable((CGLContextObj) [ctx->ctx CGLContextObj]);
	return kCVReturnSuccess;
}

@implementation GLView

- (instancetype)initWithFrame:(NSRect)frame {

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
	
	cbCtx = (CallbackContext*) malloc(sizeof(CallbackContext));
	
    NSOpenGLPixelFormat* pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs]autorelease];
    
  self = [super initWithFrame:frame pixelFormat: pixelFormat];
  if (self) 
	{
    self.wantsBestResolutionOpenGLSurface = YES;
    pf = pixelFormat;
		[self setFrame:frame];
		cbCtx->ctx = [self openGLContext];
		[cbCtx->ctx makeCurrentContext];

    cbCtx->maxiRenderer = cMaxiFactory::instance().createRenderer();
  }
  return self;
}

- (void)prepareOpenGL
{
  [super prepareOpenGL];
  
  NSRect bounds = [self bounds];
  NSRect pixels = [self convertRectToBacking:bounds];
  cbCtx->maxiRenderer->Init(pixels.size.width,pixels.size.height);
  cbCtx->maxiRenderer->SetViewport(0, 0, pixels.size.width,pixels.size.height);

  [self setupScene];
  
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink,
                                                   (CGLContextObj) [cbCtx->ctx CGLContextObj],
                                                   (CGLPixelFormatObj) [pf CGLPixelFormatObj]);
	
	CVDisplayLinkSetOutputCallback(displayLink, &Heartbeat, cbCtx);
	CVDisplayLinkStart(displayLink);
    
  // Register to be notified when the window closes so we can stop the displaylink
  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(windowWillClose:)
                                               name:NSWindowWillCloseNotification
                                             object:[self window]];
  
  printf("Vendor:   %s\n", glGetString(GL_VENDOR)                  );
  printf("Renderer: %s\n", glGetString(GL_RENDERER)                );
  printf("Version:  %s\n", glGetString(GL_VERSION)                 );
  printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

}

- (void) setupScene
{
  cMCamera* pCamera = cbCtx->maxiRenderer->GetCamera();
  pCamera->SetPosition(cMVector3Df(0, 0, 15));
  
  Quad quad;
  Cube cube;
  Sphere sphere;
  
  quad.Scale(cMVector3Df(1, 1, 1));
  quad.SetPosition(cMVector3Df(0, 0, 0));
  cbCtx->maxiRenderer->AddRenderItem(&quad);
  
  cube.Scale(cMVector3Df(1, 1, 1));
  cube.SetPosition(cMVector3Df(0, 3, 0));
  cbCtx->maxiRenderer->AddRenderItem(&cube);
  
  sphere.Scale(cMVector3Df(3, 3, 3));
  sphere.SetPosition(cMVector3Df(3, 0, 0));
  cbCtx->maxiRenderer->AddRenderItem(&sphere);
  sphere.SetMaterialColor(cMVector4Df(0, 0, 1, 1));
}

- (BOOL)acceptsFirstResponder
{
	return YES;
}

- (BOOL)becomeFirstResponder
{
	return YES;
}

- (void)dealloc
{
	CVDisplayLinkStop(displayLink);
	CVDisplayLinkRelease(displayLink);
	[pf release];
	[cbCtx->ctx release];
	free(cbCtx);
	[super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect 
{
	if(CVDisplayLinkIsRunning(displayLink))
		return;

	[[self openGLContext] flushBuffer];
}

- (void)keyDown:(NSEvent *)theEvent
{

}

- (void) windowWillClose:(NSNotification*)notification
{
    // Stop the display link when the window is closing because default
    // OpenGL render buffers will be destroyed.  If display link continues to
    // fire without renderbuffers, OpenGL draw calls will set errors.
    
    CVDisplayLinkStop(displayLink);
}

@end
