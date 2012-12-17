/*
 *  MCamera.h
 *  Maximous
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */
#ifndef __MMCAMERA3D_H__
#define __MMCAMERA3D_H__

#include "utils/MUtils.h"
#include "primitives/MObject3D.h"

enum EM_CAMERATYPE {
	eEM_Ct_Perspective,
	eEM_Ct_Orthogonal
};

class cMCamera3D: public cMObject3D
{
	
public:
	cMCamera3D(): _cameraType( eEM_Ct_Perspective ), _fovX(0), _fovY(0),
				  _near(1), _far(500) {};
	
// --- private member attribute
private:
	cMMatrix3Df		_viewMtx;
	cMMatrix3Df		_projMtx;
	EM_CAMERATYPE	_cameraType;
	float			_fovX;
	float			_fovY;
	float			_near;
	float			_far;
	float			_viewportW;
	float			_viewportH;
		
// --- private member function
private:
	void _setViewMtx();
	void _setProjMtx();
	
public:
	virtual void update();
};

#endif
