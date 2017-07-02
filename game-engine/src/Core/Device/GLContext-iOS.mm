
#import "game-engine/Core/Device/GLContext-iOS.h"
#import "game-engine/Core/Device/GLContext.h"

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
    
    this->isInitalised = [(id)self initalise];
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
    
}

-(void)makeCurrentContext
{
    currentContext = _context;
}

@end
