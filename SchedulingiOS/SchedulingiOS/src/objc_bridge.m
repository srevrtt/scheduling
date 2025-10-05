//
//  objc_bridge.m
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>

#include "objc_bridge.h"
#include <SDL2_ttf/SDL_ttf.h>

void showStatusBar(void) {
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIApplication sharedApplication].statusBarHidden = NO;
    });
    
//    NSLog(@"%@", [UIFont familyNames]);
}

// TODO: font weight
// Loads an iOS system font from a font name, and then turns it into a TTF_Font*
TTF_Font *loadSystemFont(const char *name, int fontSize) {
    // Create a Core Text descriptor for the font
    NSString *nsName = [NSString stringWithUTF8String:name];
    CTFontDescriptorRef desc =
        CTFontDescriptorCreateWithNameAndSize((__bridge CFStringRef)nsName, fontSize);
    
    if (!desc) {
        NSLog(@"Font descriptor for font %@ not found!", nsName);
        return NULL;
    }

    // Create a CTFont and extract its file URL
    CGFontRef font = CTFontCreateWithFontDescriptor(desc, fontSize, NULL);
    CFURLRef url = CTFontDescriptorCopyAttribute(desc, kCTFontURLAttribute);

    if (!url) {
        NSLog(@"No font URL for font %@!", nsName);
        CFRelease(desc);
        CFRelease(font);
        return NULL;
    }
    
    // Convert the URL to a path
    NSString *path = [(__bridge NSURL *)url path];
    
    // Load the font into an TTF_Font* for usage with SDL2
    TTF_Font *ttf_font = TTF_OpenFont([path UTF8String], fontSize);
    
    // Clean up
    CFRelease(url);
    CFRelease(font);
    CFRelease(desc);
    
    return ttf_font;
}

SDL_Texture *renderDefaultText(SDL_Renderer *renderer, const char *name,
                               const char *text, float size, SDL_Color color) {
    @autoreleasepool {
        // Convert text to NSString
        NSString *nsText = [NSString stringWithUTF8String:text ?: ""];
        NSString *nsFontName = name ? [NSString stringWithUTF8String:name] : nil;

        // Create a UIFont
        UIFont *font = [UIFont systemFontOfSize:size weight:UIFontWeightRegular];

        // Attributes (font + color)
        UIColor *uiColor = [UIColor colorWithRed:color.r/255.0
                                           green:color.g/255.0
                                            blue:color.b/255.0
                                           alpha:color.a/255.0];
        NSDictionary *attrs = @{ NSFontAttributeName: font,
                                 NSForegroundColorAttributeName: uiColor };

        // Measure text size
        CGSize size = [nsText sizeWithAttributes:attrs];
        if (size.width < 1) size.width = 1;
        if (size.height < 1) size.height = 1;

        // Draw text into an offscreen image
        UIGraphicsBeginImageContextWithOptions(size, NO, 0.0);
        [nsText drawAtPoint:CGPointZero withAttributes:attrs];
        UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();

        if (!image) return NULL;

        // Get RGBA pixel data
        CGImageRef cgImage = image.CGImage;
        NSUInteger width = CGImageGetWidth(cgImage);
        NSUInteger height = CGImageGetHeight(cgImage);

        SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, (int)width, (int)height, 32, SDL_PIXELFORMAT_ABGR8888);
        if (!surface) return NULL;

        CGContextRef context = CGBitmapContextCreate(surface->pixels,
                                                     width, height, 8, surface->pitch,
                                                     CGColorSpaceCreateDeviceRGB(),
                                                     kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedLast);
        CGContextDrawImage(context, CGRectMake(0, 0, width, height), cgImage);
        CGContextRelease(context);

        // Convert SDL_Surface → SDL_Texture
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        
        // Set blending
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        SDL_FreeSurface(surface);
        return texture;
    }
}

int *computeSafeAreaOffset(void) {
    @autoreleasepool {
        UIWindow *window = UIApplication.sharedApplication.keyWindow;
        if (!window) {
            window = [UIApplication sharedApplication].delegate.window;
        }
        
        int topInsetPoints = window.safeAreaInsets.top;
        int leftInsetPoints = window.safeAreaInsets.left;
        int dpiScale = window.screen.scale;
        
        int *offsets = malloc(2 * sizeof(int));
        offsets[0] = leftInsetPoints * dpiScale;
        offsets[1] = topInsetPoints * dpiScale;

        return offsets;
    }
}
