//
//  EAGLView.m
//  Maximous
//
//  Created by User on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"


@interface EAGLView (PrivateMethods)
- (BOOL)_createFramebuffer;
- (void)_deleteFramebuffer;
@end

@implementation EAGLView

@dynamic context;

// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained
{
	if((self = [super initWithFrame:frame])) {
		CAEAGLLayer*			eaglLayer = (CAEAGLLayer*)[self layer];
		
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000	
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking, (format == GL_RGB565) ? kEAGLColorFormatRGB565 : kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
#else
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking, (format == GL_RGB565_OES) ? kEAGLColorFormatRGB565 : kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
#endif
		_format = format;
		_depthFormat = depth;
		
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000	
#ifndef _FORCE_OPENGLES11
		_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		if(_context == nil)
#endif
#endif
		{
			_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
			if(_context == nil) {
				[self release];
				return nil;
			}
			_OPENGLES_VERSION = 1;
		}
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000			
#ifndef _FORCE_OPENGLES11
		else {
			_OPENGLES_VERSION = 2;
		}
#endif
#endif
		
		if(![self _createFramebuffer]) {
			[self release];
			return nil;
		}
	}
	
	return self;
}


//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:.
- (id)initWithCoder:(NSCoder*)coder
{
    self = [super initWithCoder:coder];
	/* if (self)
											{
												CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
												
												eaglLayer.opaque = TRUE;
												eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
																				[NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
																				kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
																				nil];
											}
											
											return self;
										 */
		
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000	
	return [self initWithFrame:[self frame] pixelFormat:GL_RGB565 depthFormat:GL_DEPTH_COMPONENT16 preserveBackbuffer:NO];
#else
	return [self initWithFrame:[self frame] pixelFormat:GL_RGB565_OES depthFormat:GL_DEPTH_COMPONENT16_OES preserveBackbuffer:NO];
#endif
	
}

- (void) releaseContext {
	[self _deleteFramebuffer];
	
	[_context release];
	_context = nil;
	
}

- (void)dealloc
{
    [self _deleteFramebuffer];    
	
	if ( _context )
    [_context release];
    
    [super dealloc];
}

+ (EAGLView *)getView
{
	return self;
}

/* - (EAGLContext *)context
{
	return context;
} */

/* - (void)setContext:(EAGLContext *)newContext
{
	if (context != newContext)
	{
		[self deleteFramebuffer];
		
		[context release];
		context = [newContext retain];
		
		[EAGLContext setCurrentContext:nil];
	}
} */

- (void)deleteFramebuffer
{
    if (_context)
    {
        [EAGLContext setCurrentContext:_context];
        
        if (defaultFramebuffer)
        {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer)
        {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
    }
}

- (void)setContext:(EAGLContext *)newContext
{
    if (_context != newContext)
    {
        [self deleteFramebuffer];
        
        [_context release];
        _context = [newContext retain];
        
        [EAGLContext setCurrentContext:nil];
    }
}

- (BOOL)_createFramebuffer
{
    if (_context && !defaultFramebuffer)
    {
        [EAGLContext setCurrentContext:_context];
        
        // Create default framebuffer object.
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        // Create color render buffer and allocate backing store.
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
	
	return YES;
}

- (void)_deleteFramebuffer
{
    if (_context)
    {
        [EAGLContext setCurrentContext:_context];
        
        if (defaultFramebuffer)
        {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer)
        {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
    }
}

 - (void)setFramebuffer // need! why??
{
	if (_context)
	{
		 [EAGLContext setCurrentContext:_context];
			
			if (!defaultFramebuffer)
				[self _createFramebuffer];
			
			glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer); 
		
		glViewport(0, 0, framebufferWidth, framebufferHeight);
	}
} 

- (BOOL)presentFramebuffer
{
    BOOL success = FALSE;
    
    if (_context)
    {
        [EAGLContext setCurrentContext:_context];
        
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        
        success = [_context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return success;
}

- (void)layoutSubviews
{
    // The framebuffer will be re-created at the beginning of the next setFramebuffer method call.
    [self _deleteFramebuffer];
}

@end
