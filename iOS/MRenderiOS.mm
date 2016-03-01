/*
 *  MRenderiOS.cpp
 *  Maximus
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#import "iOS/MRenderiOS.h"
#import	"iOS/MGraphicsiOS.h"


cMRenderiOS::cMRenderiOS()
//:_graphics( [[cMGraphicsiOS alloc] init] )
{		

}

cMRenderiOS::~cMRenderiOS()
{
	//if ( _graphics )
	//	[_graphics release];
}

void cMRenderiOS::initial()
{
	_graphics.initialize();	
}

void cMRenderiOS::draw()
{
	//[_graphics beginFrame];
	
	_graphics.createFrameBuffer();
	
	_graphics.beginFrame();
	
	
	_graphics.drawTriangle();
	//[(EAGLView *)self.view setFramebuffer];
    
		
	_graphics.endFrame();	
	 
	
}

void cMRenderiOS::setCamera( cMCamera3D *pCamera )
{
	_camera = pCamera;
	
	_camera->update();
}

