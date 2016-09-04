/*
 *  MCamera.h
 *  Maximus
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */
#ifndef __MMCAMERA3D_H__
#define __MMCAMERA3D_H__

#include "utils/MUtils.h"
#include "primitives/MObject3D.h"

namespace Maximus {

enum EM_CAMERATYPE {
	Ct_Perspective,
	Ct_Orthogonal
};

class cMCamera: public cMObject3D
{
	
public:
    cMCamera(): _cameraType(EM_CAMERATYPE::Ct_Perspective), _fovX(90.0f), _fovY(73.74f),
				  _near(1), _far(1000) {};
	
    ~cMCamera() {}
    
// --- private member attribute
private:
	cMMatrix3Df		_viewMtx;
	cMMatrix3Df		_projMtx;
	EM_CAMERATYPE	_cameraType;
	float			_fovX;
	float			_fovY;
	float			_near;
	float			_far;
	int             _viewportW;
	int             _viewportH;
		
// --- private member function
private:
	void _SetViewMtx();
	void _SetProjMtx();
	
public:
	virtual void Update();
    const cMMatrix3Df* GetViewMatrix() const;
    const cMMatrix3Df* GetProjMatrix() const;
    void SetViewPort(int width, int height);
};

} // End of namespce Maximus

#endif
