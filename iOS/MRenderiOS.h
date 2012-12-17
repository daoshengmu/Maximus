/*
 *  MRenderiOS.h
 *  Maximous
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MRENDERIOS_H__
#define __MRENDERIOS_H__

#include "interface/IMRender.h"
#include "camera/MCamera3D.h"
#include "MGraphicsiOS.h"

/*
#ifdef __OBJC__
#import <CoreFoundation/CoreFoundation.h>
#else
#include <objc/objc.h>
#endif

#ifdef __OBJC__
#include "MGraphicsiOS.h"
#else

//typedef id cMGraphicsiOS;

#endif */


class cMRenderiOS :public IMRender 
{
private:
 	cMGraphicsiOS	_graphics;
	cMCamera3D*		_camera;

public:
	cMRenderiOS();
	~cMRenderiOS();
	
	virtual void initial();
	virtual void draw();
	virtual void setCamera( cMCamera3D *pCamera );
};

#endif
