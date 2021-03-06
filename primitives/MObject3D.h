/*
 *  MObject3D.h
 *  Maximous
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MOBJECT3D_H__
#define __MOBJECT3D_H__

#include "utils/MUtils.h"

class cMObject3D
{
private:
	cMVector3Df	_origin;
	cMVector3Df	_scale;	
	
protected:
	cMMatrix3Df	worldMtx_;
	bool		update_;
	
public:
	//--------------------------------------------------------------------------------------
    /// @brief Constructor
    //--------------------------------------------------------------------------------------	
	cMObject3D();
	
	//--------------------------------------------------------------------------------------
    /// @brief Destructor
    //--------------------------------------------------------------------------------------
	virtual ~cMObject3D();
	
	virtual void update();

	const cMVector3Df* getPosition() const;
	
	void getPosition( cMVector3Df* vect );
};

#endif
