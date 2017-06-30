#ifndef _CONTEXTIOS_H
#define _CONTEXTIOS_H

#import <GLKit/GLKit.h>

@interface ContextiOS : NSObject

@property (readwrite, nonatomic, strong) EAGLContext *context;

-(BOOL)initalise;
-(void)makeCurrentContext;
+(EAGLContext *)currentContext;

@end

#endif /* _CONTEXTIOS_H */
