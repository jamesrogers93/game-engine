#ifndef _AIFSM_H
#define _AIFSM_H

// STD
#include <unordered_map>

// Main Core
#include "game-engine/Entity/Property.h"

// AI
#include "game-engine/Modules/AI/AIFSMState.h"

class AIFSM : public Property
{
private:
    std::unordered_map<std::string, AIFSMState*> states;
    std::string currentState;
    
    //std::vector<AIFSMState*> states;
    //int currentState;
    
public:
    AIFSM(const std::string &name) : Property(name, Property::AI_FSM)
    {}
    
    void setCurrentState(const std::string &state) { this->currentState = state; }
    std::string getCurrentState() { return currentState; }
    
    bool addState(const std::string &name, AIFSMState *state)
    {
        auto it = states.find(name);
        
        if(it == states.end())
        {
            states[name] = state;
            return true;
        }
        
        return false;

    }
    
    bool makeActive();
    bool makeUnactive();
    
    void update();
    
};

#endif /* _AIFSM_H */
