#ifndef _AR_H
#define _AR_H

// STD
#include <string>
#include <map>

// Game Engine
#include "game-engine/Core/Modules/CoreModule.h"
#include "game-engine/Core/Modules/AR/AREntity.h"
#include "game-engine/Core/Modules/AR/ARView.h"

class AR : public CoreModule
{
public:
    
    static AR& getInstance()
    {
        static AR instance;
        return instance;
    }
    
    bool initalise();
    bool deinitalise();
    bool update();
    
    bool addAREntity(const std::string &name, AREntity *entity);
    bool setActiveAREntity(const std::string &name);
    
private:
    
    ARView view;
    
    std::map<std::string, AREntity *> arEntities;
    std::string activeAREntity;
    
    AR();
    AR(AR const&);              // Don't Implement
    void operator=(AR const&);		// Don't implement
    
};

#endif /* _AR_H */
