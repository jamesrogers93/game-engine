#include "game-engine/Entity/Property.h"

const bool Property::DEFAULT_ACTIVE = false;

Property::Property(const std::string &name, const Type &type) : mName(name), mType(type), mActive(DEFAULT_ACTIVE)
{
}

Property::~Property()
{
    mOwner = NULL;
}

void Property::setOwner(Entity *owner)
{
    mOwner = owner;
}


const std::string Property::typeToString() const
{
    switch(this->mType)
    {
        case Property::MESH:
            return "mesh";
        case Property::ANIMATABLE_MESH:
            return "animatable_mesh";
        case Property::DIRECTIONAL_LIGHT:
            return "directional_light";
        case Property::POINT_LIGHT:
            return "point_light";
        default:
            return "";
    }
}
