/*
 *  MUtils.h
 *  Maximus
 *
 *  Created by User on 5/29/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MUTILS_H__
#define __MUTILS_H__

#include <assert.h>
#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

#include "util/MTypes.h"
#include "util/MMath.h"

#include "util/MVector3D.h"
#include "util/MVector4D.h"
#include "util/MMatrix3D.h"

namespace Maximus
{

typedef cMVector3D<float> cMVector3Df;
typedef cMVector4D<float> cMVector4Df;
typedef cMMatrix3D<float> cMMatrix3Df;

} // End of namespace Maximus

using namespace std;

#endif
