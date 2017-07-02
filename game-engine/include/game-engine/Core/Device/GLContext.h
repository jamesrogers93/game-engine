#ifndef _CONTEXT_H
#define _CONTEXT_H

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
    
private:
    
    GLContext();
    ~GLContext();
    
    GLContext(GLContext const&);        // Don't Implement
    void operator=(GLContext const&);		// Don't implement
    
    void *self;
    bool isInitalised;
    
};

#endif /* _CONTEXT_H */
