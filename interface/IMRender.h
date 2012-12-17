/*
 *  IRender.h
 *  Maximous
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __IMRENDER_H__
#define __IMRENDER_H__

#include "camera/MCamera3D.h"

class IMRender
{
public:
	virtual ~IMRender() {};
	virtual void initial() = 0;
	virtual void draw() = 0;
	virtual void setCamera( cMCamera3D *pCamera ) = 0;
};

#endif