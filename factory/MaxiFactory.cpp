/*
 *  MaxiFactory.cpp
 *  Maximous
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#include "factory/MaxiFactory.h"
#ifdef __MOS_IOS__
#include "iOS/MRenderiOS.h"
#endif

#include "interface/IMRender.h"

IMRender* cMaxiFactory::createRenderer( void )
{
	return new cMRenderiOS();//::instance();  // need to be del.
}