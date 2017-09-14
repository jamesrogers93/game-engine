#ifndef _AIDT_H
#define _AIDT_H

#include "game-engine/Entity/Property.h"

class AIDT : public Property
{
public:
    
    AIDT(const std::string &name) : Property(name, Property::AI_DT)
    {}
    
    bool update()
    {}
};

#endif /* _AIDT_H */
