#ifndef _ANIMATION_H
#define _ANIMATION_H

// STD
#include <vector>

#include "game-engine/Modules/Animation/KeyFrame.h"

class Animation
{
public:
    Animation()
    {}
    
private:
    std:vector<KeyFrame> keyframes;
};

#endif /* _ANIMATION_H */
