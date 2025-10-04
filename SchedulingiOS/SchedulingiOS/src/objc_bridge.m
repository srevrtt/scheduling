//
//  objc_bridge.m
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#import <UIKit/UIKit.h>
#import "objc_bridge.h"

void showStatusBar(void) {
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIApplication sharedApplication].statusBarHidden = NO;
    });
}
