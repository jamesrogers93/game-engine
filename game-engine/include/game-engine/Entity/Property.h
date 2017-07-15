#ifndef _PROPERTY_H
#define _PROPERTY_H

#include <string>
class Entity;

class Property
{
protected:
    std::string mName;
    
    Entity *mOwner;
    
public:
    Property(const std::string &name);
    
    void setOwner(Entity *owner);
};

#endif /* _PROPERTY_H */
