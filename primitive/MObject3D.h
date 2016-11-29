/*
 *  MObject3D.h
 *  
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MOBJECT3D_H__
#define __MOBJECT3D_H__

#include "util/MUtils.h"

namespace Maximus {

class Material;
    
class cMObject3D
{
public:
	//--------------------------------------------------------------------------------------
    /// @brief Constructor
    //--------------------------------------------------------------------------------------	
	cMObject3D();
	
	//--------------------------------------------------------------------------------------
    /// @brief Destructor
    //--------------------------------------------------------------------------------------
	virtual ~cMObject3D();
	
	virtual void Update();
	const cMVector3Df* GetPosition() const;
	void GetPosition(cMVector3Df* vect);
  void SetPosition(const cMVector3Df& pos);
  void Scale(const cMVector3Df& aScale);
  void RotateX(float aDegree);
  void RotateY(float aDegree);
  void RotateZ(float aDegree);

protected:
  shared_ptr<cMMatrix3Df>	mWorldMtx;
  bool		mUpdate;
  cMVector3Df	mOrigin;
  cMVector3Df	mScale;
  MQuaternionf mRotate;

};
}

#endif
