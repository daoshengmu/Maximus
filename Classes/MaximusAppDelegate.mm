//
//  MaximusAppDelegate.m
//  Maximus
//
//  Created by User on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MaximusAppDelegate.h"
//#import "MaximousViewController.h"

@implementation MaximusAppDelegate

@synthesize _window;
//@synthesize _viewController;
@synthesize _glView;

#define kFPS	60.0

- (void)applicationWillResignActive:(UIApplication *)application
{
  //  [viewController stopAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
  //  [viewController startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
  //  [viewController stopAnimation];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Handle any background procedures not related to animation here.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Handle any foreground procedures not related to animation here.
}

- (void)update
{
	[_glView setFramebuffer];
	_renderer.draw();
	/* if(!shell->UpdateScene())
			printf("UpdateScene error\n");
		
		if(!shell->RenderScene())
			printf("RenderScene error\n");
		
		[_glView swapBuffers];
	 */	
	[_glView presentFramebuffer];
}

- (void)applicationDidFinishLaunching:(UIApplication *)application {    
	
	
	//if(!shell->InitApplication())
	//	printf("InitApplication error\n");

	// Override point for customization after application launch
	//[window makeKeyAndVisible];
	_renderer.initial();
	// create our rendering timer
	[NSTimer scheduledTimerWithTimeInterval:(1.0 / kFPS) target:self selector:@selector(update) userInfo:nil repeats:YES];
		
	printf("<#message#>");

}

- (void)dealloc
{
    //[viewController release];
    [window release];
    
    [super dealloc];
}

@end
