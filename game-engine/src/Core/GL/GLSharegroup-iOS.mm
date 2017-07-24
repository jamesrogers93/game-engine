
#import "game-engine/Core/GL/GLSharegroup-iOS.h"
#import "game-engine/Core/GL/GLSharegroup.h"

@interface GLSharegroupIOS()
{
    
}
@end

@implementation GLSharegroupIOS

-(id)initWithContext:(EAGLContext *) context
{
    self = [super init];
    
    if(self)
    {
        _sharegroup = context.sharegroup;
    }
    return self;
}

@end
