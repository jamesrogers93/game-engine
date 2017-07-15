#include "game-engine/Entity/Property.h"

Property::Property(const std::string &name, const Type &type) : mName(name), mType(type)
{
    
}

void Property::setOwner(Entity *owner)
{
    mOwner = owner;
}
