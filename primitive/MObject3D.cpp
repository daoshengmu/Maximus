/*
 *  MObject3D.cpp
 *  Maximus
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "primitive/MObject3D.h"

namespace Maximus
{

cMObject3D::cMObject3D()
: mUpdate(true), mWorldMtx(make_shared<cMMatrix3Df>())
{}

cMObject3D::~cMObject3D()
{}

void cMObject3D::Update()
{
  if (mUpdate)
  {
    mWorldMtx->identity();
    mWorldMtx->scale(mScale);
    mWorldMtx->translate(mOrigin);
    // TODO: Rotate
    
    mUpdate = false;
  }
}

const cMVector3Df* cMObject3D::GetPosition() const
{
	return &mOrigin;
}

void cMObject3D::GetPosition(cMVector3Df* vect)
{
  *vect = mOrigin;
  mUpdate = true;
}

void cMObject3D::SetPosition(const cMVector3Df& pos)
{
  mOrigin = pos;
  mUpdate = true;
}
  
void cMObject3D::Scale(const cMVector3Df& aScale)
{
  mScale = aScale;
  mUpdate = true;
}

} // End of namespace Maximus
