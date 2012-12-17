//
//  main.m
//  Maximous
//
//  Created by User on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "iOS/MGraphicsiOS.h"
#include "utils/MUtils.h"
#include "camera/MCamera3D.h"
#include "primitives/MObject3D.h"
#include "factory/MaxiFactory.h"
#include "interface/IMRender.h"

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	cMVector3D<float> testV;

	cMObject3D obj;
	
	
	cMVector3Df a(testV);
	
	cMMatrix3Df b;
	cMMatrix3Df mtx(b);
	
	//cMGraphicsiOS *g = [[cMGraphicsiOS alloc] init];
	
	cMCamera3D	camera;
	IMRender	*pRenderer = NULL;
	//[g beginFrame];
	
	pRenderer = cMaxiFactory::instance().createRenderer();
		
	pRenderer->setCamera( &camera );
	mtx.setValueToItem(0, 3, 0.5);
	
		
    int retVal = UIApplicationMain(argc, argv, nil, nil);	
	
	delete pRenderer;
	
	//[g release];
    [pool release];
    return retVal;
}
