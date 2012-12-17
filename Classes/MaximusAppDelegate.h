//
//  MaximusAppDelegate.h
//  Maximous
//
//  Created by User on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "iOS/MRenderiOS.h"
#import "iOS/EAGLView.h"

//@class MaximusViewController;

@interface MaximusAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
 //   MaximousViewController *viewController;
	cMRenderiOS _renderer; 
	EAGLView *_glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *_window;
//@property (nonatomic, retain) IBOutlet MaximusViewController *_viewController;
@property (nonatomic, retain) IBOutlet EAGLView *_glView;

@end

