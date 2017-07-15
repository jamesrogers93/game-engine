#ifndef _OBJECT_H
#define _OBJECT_H

#include "game-engine/Core/Entity/Entity.h"

class Object : public Entity
{
    
    Object(const std::string &name) : Entity(name)
    {}
    
public:
    
    void initialise(){}
    void update(){}
};

#endif /* _OBJECT_H */
