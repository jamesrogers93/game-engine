#ifndef _CONTEXTIOS_H
#define _CONTEXTIOS_H

#import <GLKit/GLKit.h>

@interface GLContextIOS : NSObject

@property (readwrite, nonatomic, strong) EAGLContext *context;

-(BOOL)initalise;
-(BOOL)deinitalise;
-(void)makeCurrentContext;
-(EAGLContext *)getContext;
-(EAGLSharegroup *)getSharegroup;
+(EAGLContext *)currentContext;

@end

#endif /* _CONTEXTIOS_H */
