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

void cMObject3D::Update()
{}

const cMVector3Df* cMObject3D::GetPosition() const
{
	return &_origin;
}

void cMObject3D::GetPosition(cMVector3Df* vect)
{
    *vect = _origin;
}

void cMObject3D::SetPosition(const cMVector3Df& pos)
{
    _origin = pos;
}