#include "game-engine/Entity/Property.h"

Property::Property(const std::string &name) : mName(name)
{
    
}

void Property::setOwner(Entity *owner)
{
    mOwner = owner;
}
