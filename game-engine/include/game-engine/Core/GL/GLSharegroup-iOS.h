#ifndef _GLSHAREGROUPIOS_H
#define _GLSHAREGROUPIOS_H

#import <GLKit/GLKit.h>

@interface GLSharegroupIOS : NSObject

@property (readwrite, nonatomic, strong) EAGLSharegroup *sharegroup;

-(id)initWithContext:(EAGLContext *) context;

@end

#endif /* _GLSHAREGROUPIOS_H */
