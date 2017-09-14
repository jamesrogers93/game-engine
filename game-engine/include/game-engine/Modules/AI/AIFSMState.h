#ifndef _AIFSMSTATE_H
#define _AIFSMSTATE_H

// STD
#include <string>

#include "game-engine/Entity/Entity.h"


class AIFSMState
{
private:
    Entity *parent;
    
public:
    
    AIFSMState(Entity *parent) : parent(parent)
    {}
    
    virtual const std::string update() = 0;
};

#endif /* _AIFSMSTATE_H */
