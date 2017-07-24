#ifndef _GLSHAREGROUP_H
#define _GLSHAREGROUP_H

class GLSharegroup
{
public:
    GLSharegroup()
    {}
    
    ~GLSharegroup()
    {}
    
    void setSharegroup(void *sharegroup)
    {
        self = sharegroup;
    }
    
private:
    
    void *self;
};

#endif /* _GLSHAREGROUP_H */
