#ifndef _AI_H
#define _AI_H

// STD
#include <string>
#include <map>

// Game Engine AR
#include "game-engine/Core/Main/CoreModule.h"

class AIFSM;
class AIDT;

class AI : public CoreModule
{
public:
    
    static AI& getInstance()
    {
        static AI instance;
        return instance;
    }
    
    bool initialise();
    bool deinitialise();
    bool update();
    
    bool addFSMProperty(const std::string &name, AIFSM *property);
    bool addDTProperty(const std::string &name, AIDT *property);
    
    bool removeFSMProperty(const std::string &name);
    bool removeDTProperty(const std::string &name);
    
private:
    
    std::map<std::string, AIFSM*> fsms;
    std::map<std::string, AIDT*> dts;
    
    AI();
    AI(AI const&);              // Don't Implement
    void operator=(AI const&);  // Don't implement
    
};

#endif /* _AI_H */
