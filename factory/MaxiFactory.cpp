/*
 *  MaxiFactory.cpp
 *  Maximus
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "factory/MaxiFactory.h"
#include "MRender.h"

namespace Maximus
{
    
cMaxiFactory::cMaxiFactory()
{
    
}

cMaxiFactory::~cMaxiFactory()
{
    
}

cMRender* cMaxiFactory::createRenderer()
{
  return &cMRender::GetInstance();
}

}
