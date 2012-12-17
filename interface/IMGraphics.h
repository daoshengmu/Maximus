/*
 *  untitled.h
 *  Maximous
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __IMGRAPHICS_H__
#define __IMGRAPHICS_H__

class IMGraphics
{
public:
	virtual	~IMGraphics() {};
	virtual void initialize() = 0;
	virtual void drawTriangle() = 0;
	virtual void createFrameBuffer() = 0;
	virtual void beginFrame() = 0;
	virtual void endFrame() = 0;
};

#endif