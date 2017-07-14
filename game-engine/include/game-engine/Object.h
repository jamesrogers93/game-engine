#ifndef _OBJECT_H
#define _OBJECT_H

#include "game-engine/Core/Entity/ENode.h"

class Object : public ENode
{
    
    Object(const std::string &name) : ENode(name)
    {}
    
public:
    
    void initialise(){}
    void update(){}
};

#endif /* _OBJECT_H */
