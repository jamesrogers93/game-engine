
#import "game-engine/Core/Modules/Graphics/Context-iOS.h"
#import "game-engine/Core/Modules/Graphics/Context.h"

@interface ContextiOS()
{
    
}
@end

@implementation ContextiOS

static EAGLContext *currentContext = NULL;

+(EAGLContext *)currentContext
{
    return currentContext;
}

Context::Context()
{
    self = [[ContextiOS alloc] init];
}

Context::~Context()
{
    [(id)self dealloc];
}

void Context::initialise()
{
    this->isInitalised = [(id)self initalise];
}

void Context::makeCurrentContext()
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

-(void)makeCurrentContext
{
    currentContext = _context;
}

@end
