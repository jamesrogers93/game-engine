#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "game-engine/Core/Main/Entity.h"

class GameObject : public Entity
{
public:
    GameObject(const std::string &name) : Entity(name, Entity::GAME_OBJECT)
    {}
    
    virtual void initialise(){}
    virtual void deinitialise(){}
    //void update(){}
};

#endif /* _GAMEOBJECT_H */
