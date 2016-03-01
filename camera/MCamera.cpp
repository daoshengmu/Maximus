/*
 *  MCamera.cpp
 *  Maximus
 *
 *  Created by User on 6/5/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "camera/MCamera3D.h"

namespace Maximous
{

void cMCamera::_setViewMtx()
{	
	//float view[16] = { worldMtx_[0], worldMtx_[1], worldMtx_[2], worldMtx_[3], 
//					   worldMtx_[4], worldMtx_[5], worldMtx_[6], worldMtx_[7],
//					   worldMtx_[8], worldMtx_[9], worldMtx_[10], worldMtx_[11],
//								0.0,		  0.0,			 0.0,			0.0 };
	
	//_viewMtx.setRawData( view, 16 );
	_viewMtx = cMMatrix3Df( worldMtx_[0], worldMtx_[1], worldMtx_[2], worldMtx_[3], 
						   worldMtx_[4], worldMtx_[5], worldMtx_[6], worldMtx_[7],
						   worldMtx_[8], worldMtx_[9], worldMtx_[10], worldMtx_[11],
						            0.0,		  0.0,			 0.0,			0.0 );
	
	const cMVector3Df* pos = getPosition();
		
	_viewMtx.translate( *pos );	  // need to check...
}

void cMCamera::_setProjMtx()
{
	if ( _cameraType == eEM_Ct_Perspective )
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
	else if ( _cameraType == eEM_Ct_Orthogonal )
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
		assert( 0 ); // "unKnown camera type"
	}

}

void cMCamera::update()
{
	if ( update_ )
	{
		_setViewMtx();
		update_ = false;
	}
}
    
}
