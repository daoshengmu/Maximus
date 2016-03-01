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

//cMaxiFactory& operator = (const cMaxiFactory& rhs)
//{
//    this = rhs;
//    return this;
//}

cMRender* cMaxiFactory::createRenderer()
{
    static cMRender render;
    return &render;//::instance();  // need to be del.
}

}