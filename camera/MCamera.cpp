/*
 *  MCamera.cpp
 *  Maximus
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "camera/MCamera.h"
#include <Math.h>

namespace Maximus
{

void cMCamera::_SetViewMtx()
{
  cMVector3Df origin(*GetPosition());
  
  origin *= -1;
  
  float* items = mWorldMtx->GetItems();
	_viewMtx.SetItems( items[0], items[4], items[8], 0.0,
                     items[1], items[5], items[9], 0.0,
                     items[2], items[6], items[10], 0.0,
                     origin.x, origin.y,  origin.z, 1.0 );

   // _viewMtx = cMMatrix3Df();
	//const cMVector3Df* pos = GetPosition();
	//_viewMtx.translate( *pos );	  // need to check...
}

void cMCamera::_SetProjMtx()
{
	if ( _cameraType == Ct_Perspective )
	{
		float fov_x;
		float fov_y;
		float Q;		
		
		fov_x =  M_DEGREE_TO_RADIAN( _fovX );
		fov_y =  M_DEGREE_TO_RADIAN( _fovY );
		Q     =  _far / ( _far - _near ); 
		
		_projMtx = cMMatrix3Df(  1.0f/tan(fov_x*0.5f), 0.0f                , 0.0f          , 0.0f,
								  0.0f                , 1.0f/tan(fov_y*0.5f), 0.0f          , 0.0f,
								  0.0f                , 0.0f                , Q             , 1.0f,
								  0.0f                , 0.0f                , (-_near * Q) , 0.0f );
	}
	else if ( _cameraType == Ct_Orthogonal )
	{
		float l = -_viewportW * 0.5;
		float r = _viewportW * 0.5;
		float b = -_viewportH * 0.5;
		float t = _viewportH * 0.5;	
		
		_projMtx = cMMatrix3Df(  2.0f/(r-l)         , 0.0f            , 0.0f						, 0.0f,
								  0.0f	               , 2.0f/(t-b)  		 , 0.0f						, 0.0f,
								  0.0f		           , 0.0f                , 1.0f/(_far - _near)    , 0.0f,
								  -(l+r)/(r-l)		   , -(t+b)/(t-b)        , -_near/(_far-_near)	, 1.0f );
	}
	else 
	{
		assert(0 && "unKnown camera type");
	}

}

void cMCamera::Update()
{
	if (mUpdate)
	{
		_SetViewMtx();
    _SetProjMtx();

		mUpdate = false;
	}
}
    
const cMMatrix3Df* cMCamera::GetViewMatrix() const
{
    return &_viewMtx;
}
    
const cMMatrix3Df* cMCamera::GetProjMatrix() const
{
    return &_projMtx;
}
    
void cMCamera::SetViewPort(int width, int height)
{
    _viewportW = width;
    _viewportH = height;
}

}
