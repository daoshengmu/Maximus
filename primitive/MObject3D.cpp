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
: mUpdate(true), mWorldMtx(make_shared<cMMatrix3Df>()),
  mScale(1.0, 1.0, 1.0)
{}

cMObject3D::~cMObject3D()
{}

void cMObject3D::Update()
{
  if (mUpdate)
  {
    mWorldMtx->Identity();
    mWorldMtx->Scale(mScale);
    cMMatrix3Df rotateMtx(mRotate.CovertToMatrix3D());
    *mWorldMtx *= rotateMtx;
    mWorldMtx->Translate(mOrigin);
    
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

void cMObject3D::RotateX(float aDegree)
{
  float radianX = M_DEGREE_TO_RADIAN(aDegree);
  MQuaternionf quat(sin((float)(radianX / 2.0f)), 0.0f, 0.0f,
                    cos((float)(radianX / 2.0f)));
  quat *= mRotate;
  mRotate = quat;

  mUpdate = true;
}

void cMObject3D::RotateY(float aDegree)
{
  float radianY = M_DEGREE_TO_RADIAN(aDegree);
  MQuaternionf quat(0.0f, sin((float)(radianY / 2.0)), 0.0f,
                    cos((float)(radianY / 2.0f)));
  quat *= mRotate;
  mRotate = quat;
  
  mUpdate = true;
}

void cMObject3D::RotateZ(float aDegree)
{
  float radianZ = M_DEGREE_TO_RADIAN(aDegree);
  MQuaternionf quat(0.0f, 0.0f, sin((float)(radianZ / 2.0)),
                    cos((float)(radianZ / 2.0f)));
  quat *= mRotate;
  mRotate = quat;
  
  mUpdate = true;
}
  
} // End of namespace Maximus
