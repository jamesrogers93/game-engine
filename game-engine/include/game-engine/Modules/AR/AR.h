#ifndef _AR_H
#define _AR_H

// STD
#include <string>
#include <map>

// Game Engine AR
#include "game-engine/Modules/CoreModule.h"
#include "game-engine/Modules/AR/AREntity.h"

class AR : public CoreModule
{
public:
    
    static AR& getInstance()
    {
        static AR instance;
        return instance;
    }
    
    bool initialise();
    bool deinitialise();
    bool update();
    
    bool addAREntity(const std::string &name, AREntity *entity);
    bool removeAREntity(const std::string &name);
    bool setActiveAREntity(const std::string &name);
    
private:
    
    std::map<std::string, AREntity *> arEntities;
    AREntity* activeAREntity;
    
    AR();
    AR(AR const&);              // Don't Implement
    void operator=(AR const&);		// Don't implement
    
};

#endif /* _AR_H */
