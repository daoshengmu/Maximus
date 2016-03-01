//
//  MGraphicsiOS.h
//  Maximus
//
//  Created by User on 6/5/11.
//  Copyright 2011 Daosheng Mu. All rights reserved.
//

#ifndef __MGRAPHICSIOS_H__
#define __MGRAPHICSIOS_H__


#include "interface/IMGraphics.h"


class cMGraphicsiOS : public IMGraphics 
{
	//class EAGLView;		// forward declaration
	
private:
	//EAGLContext *context;
//	EAGLView  *_pView;
	
public:
	cMGraphicsiOS();
	~cMGraphicsiOS();
		
	virtual void initialize();
	virtual bool loadShaders();
	virtual void drawTriangle();
	virtual void createFrameBuffer();
	virtual void beginFrame();
	virtual void endFrame();
	
};

/* @interface GraphicsDelegate {
  //  UIWindow *window;
	EAGLView *glView;
} */

//@property (nonatomic, retain) IBOutlet UIWindow *window;
//@property (nonatomic, retain) IBOutlet EAGLView *glView;

//@end

#endif