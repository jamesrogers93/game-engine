#include "game-engine/Modules/AI/AIFSM.h"
#include "game-engine/Modules/AI/AI.h"

bool AIFSM::makeActive()
{
    this->mActive = true;
    
    return AI::getInstance().addFSMProperty(this->mName, this);
}

bool AIFSM::makeUnactive()
{
    this->mActive = false;
    
    return AI::getInstance().removeFSMProperty(this->mName);
}

void AIFSM::update()
{
    auto it = states.find(currentState);
    
    if(it != states.end())
    {
        currentState = states.at(currentState)->update();
    }
}
