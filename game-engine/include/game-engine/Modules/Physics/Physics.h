#ifndef _PHYSICS_H
#define _PHYSICS_H

// STD
#include <string>
#include <map>

// Game Engine AR
#include "game-engine/Modules/CoreModule.h"

class PhysicsProperty;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btCollisionWorld;

class Physics : public CoreModule
{
public:
    
    static Physics& getInstance()
    {
        static Physics instance;
        return instance;
    }
    
    bool initialise();
    bool deinitialise();
    bool update();
    
    bool addPhysicsProperty(const std::string &name, PhysicsProperty *entity);
    bool removePhysicsProperty(const std::string &name);
    
private:
    
    std::map<std::string, PhysicsProperty *> physicsProperties;
    
    btCollisionConfiguration* bt_collision_configuration;
    btCollisionDispatcher* bt_dispatcher;
    btBroadphaseInterface* bt_broadphase;
    btCollisionWorld* bt_collision_world;
    
    Physics();
    Physics(Physics const&);              // Don't Implement
    void operator=(Physics const&);		// Don't implement
    
};

#endif /* _AR_H */
