/*
 *  MObject3D.cpp
 *  Maximus
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "primitives/MObject3D.h"

//-----------------------------------------
cMObject3D::cMObject3D()
: update_(true)
{}
//End of constructor for cMObject3D---------

cMObject3D::~cMObject3D()
{}

void cMObject3D::update()
{}

const cMVector3Df* cMObject3D::getPosition() const
{
	return &_origin;
}

void cMObject3D::getPosition( cMVector3Df* vect )
{
	memcpy( vect, &_origin, sizeof( _origin ) );
}
