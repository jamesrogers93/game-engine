
#import "game-engine/Core/GL/GLContext-iOS.h"
#import "game-engine/Core/GL/GLContext.h"

#import "game-engine/Core/GL/GLSharegroup-iOS.h"

@interface GLContextIOS()
{
    
}
@end

@implementation GLContextIOS

static EAGLContext *currentContext = NULL;

+(EAGLContext *)currentContext
{
    return currentContext;
}

void GLContext::initialise()
{
    self = [[GLContextIOS alloc] init];
    
    this->isInitialised = [(id)self initalise];
    
    // Now we should create the sharegroup with a reference to the context sharegroup
    //GLSharegroupIOS *sharegroup = [[GLSharegroupIOS alloc] initWithContext: [(id)self getContext]];
    //mSharegroup.setSharegroup(sharegroup);
}

void GLContext::deinitialise()
{
    [(id)self deinitalise];
    
    [(id)self dealloc];
}

void GLContext::makeCurrentContext()
{
    [(id)self makeCurrentContext];
}

-(BOOL)initalise
{
    if(!_context)
    {
        _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    }
    
    if (!_context)
    {
        NSLog(@"Failed to create ES context");
        return false;
    }
    
    [EAGLContext setCurrentContext:_context];
    
    return true;
}

-(BOOL)deinitalise
{
    return true;
}

-(void)makeCurrentContext
{
    [EAGLContext setCurrentContext:_context];
    currentContext = _context;
}

-(EAGLContext *)getContext
{
    return _context;
}

-(EAGLSharegroup *)getSharegroup
{
    return _context.sharegroup;
}

@end
