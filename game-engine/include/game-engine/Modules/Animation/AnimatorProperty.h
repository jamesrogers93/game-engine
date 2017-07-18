#ifndef _ANIMATORPROPERTY_H
#define _ANIMATORPROPERTY_H

// STD
#include <string>

#include "game-engine/Entity/Property.h"

class AnimatorProperty : public Property
{
public:
    AnimatorProperty(const std::string &name) : Property(name, Property::ANIMATOR)
    {}
    
private:
    
    std::string animationKey;
}

#endif /* _ANIMATORPROPERTY_H */
