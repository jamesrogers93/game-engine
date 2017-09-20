#include "game-engine/Modules/Physics/Physics.h"
#include "game-engine/Modules/Physics/PhysicsProperty.h"

#include "game-engine/Core/Main/Entity.h"

#include <iostream>

// Bullet
#include <btBulletCollisionCommon.h>

Physics::Physics() : CoreModule(CoreModuleType::CM_PHYSICS)
{}

bool Physics::initialise()
{
    
    double scene_size = 1000;
    unsigned int max_objects = 100;
    
    bt_collision_configuration = new btDefaultCollisionConfiguration();
    bt_dispatcher = new btCollisionDispatcher(bt_collision_configuration);
    
    btScalar sscene_size = (btScalar) scene_size;
    btVector3 worldAabbMin(-sscene_size, -sscene_size, -sscene_size);
    btVector3 worldAabbMax(sscene_size, sscene_size, sscene_size);
    
    //This is one type of broadphase, bullet has others that might be faster depending on the application
    bt_broadphase = new bt32BitAxisSweep3(worldAabbMin, worldAabbMax, max_objects, 0, true);  // true for disabling raycast accelerator
    
    bt_collision_world = new btCollisionWorld(bt_dispatcher, bt_broadphase, bt_collision_configuration);
    
    return true;
}

bool Physics::deinitialise()
{
    return true;
}

bool Physics::update()
{
    
    // Update property positions and call before collision test callbacks
    
    for(auto property : physicsProperties)
    {
        const Entity* owner = property.second->getOwner();
        
        property.second->setWorldTransform(glm::vec3(owner->getGlobalModel()[3]));

        // Before collision test callback function
        property.second->getBeforeCollisionTestCallback()(property.second);
    }
    
    // TEST
    //static unsigned int test_counter = 0; btSimdFloat4) mVec128 = (152.579819, 129.840393, -0.722387075, 0)
    // END TEST                             btSimdFloat4) mVec128 = (152.579819, 129.840393, -0.722387075, 0)
    
    // Perform collision detection
    bt_collision_world->performDiscreteCollisionDetection();
    
    int numManifolds = bt_collision_world->getDispatcher()->getNumManifolds();
    
    //For each contact manifold
    for (int i = 0; i < numManifolds; i++) {
        btPersistentManifold* contactManifold = bt_collision_world->getDispatcher()->getManifoldByIndexInternal(i);
        const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
        const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
        contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
        int numContacts = contactManifold->getNumContacts();
        //For each contact point in that manifold
        for (int j = 0; j < numContacts; j++) {
            //Get the contact information
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            
            //std::cout << "COLLISION!!! " << test_counter << std::endl;
            //test_counter++;
            
            // Get the physics properties that own the collision objects
            PhysicsProperty *obAA = (PhysicsProperty*)obA->getUserPointer();
            PhysicsProperty *obBB = (PhysicsProperty*)obB->getUserPointer();
            
            obAA->getCollisionCallback()(obAA, obBB, &pt);
            obBB->getCollisionCallback()(obAA, obBB, &pt);
            
        }
    }
    
    
    return true;
}

bool Physics::addPhysicsProperty(const std::string &name, PhysicsProperty *entity)
{
    auto it = physicsProperties.find(name);
    
    if(it == physicsProperties.end())
    {
        physicsProperties[name] = entity;
        if(entity->getIsMaskSet())
        {
            bt_collision_world->addCollisionObject(entity->collisionObject, entity->getCollisionMask(), entity->getCollidesWithMask());
        }
        else
        {
            bt_collision_world->addCollisionObject(entity->collisionObject);
        }
        
        return true;
    }

    return false;
}

bool Physics::removePhysicsProperty(const std::string &name)
{
    auto it = physicsProperties.find(name);
    
    if(it != physicsProperties.end())
    {
        bt_collision_world->removeCollisionObject(it->second->collisionObject);
        physicsProperties.erase(it);
        return true;
    }
    
    return false;
}
