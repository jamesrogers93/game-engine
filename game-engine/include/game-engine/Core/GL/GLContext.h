#ifndef _CONTEXT_H
#define _CONTEXT_H

//#include "game-engine/Core/GL/GLSharegroup.h"

class GLContext
{
public:
    
    static GLContext& getInstance()
    {
        static GLContext instance;
        return instance;
    }
    
    void initialise();
    void deinitialise();
    void makeCurrentContext();
    
    //const GLSharegroup* getSharegroup() const {  return isInitialised ? &mSharegroup : 0; }
    
private:
    
    GLContext();
    ~GLContext();
    
    GLContext(GLContext const&);        // Don't Implement
    void operator=(GLContext const&);		// Don't implement
    
    void *self;
    
    //GLSharegroup mSharegroup;
    
    bool isInitialised;
    
    void initialise2();
};

#endif /* _CONTEXT_H */
