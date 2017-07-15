#ifndef _PROPERTY_H
#define _PROPERTY_H

#include <string>
class Entity;

class Property
{
public:
    enum Type
    {
        MESH, ANIMATABLE_MESH, DIRECTIONAL_LIGHT, POINT_LIGHT, 
    };
    
protected:
    std::string mName;
    Type mType;
    
    Entity *mOwner;
    
public:
    Property(const std::string &name, const Type &type);
    
    void setOwner(Entity *owner);
};

#endif /* _PROPERTY_H */
