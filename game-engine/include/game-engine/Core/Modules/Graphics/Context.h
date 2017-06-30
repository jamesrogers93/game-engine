#ifndef _CONTEXT_H
#define _CONTEXT_H

class Context
{
private:
    void *self;
    bool isInitalised;
    
public:
    Context();
    ~Context();
    void initialise();
    void makeCurrentContext();
    
};

#endif /* _CONTEXT_H */
