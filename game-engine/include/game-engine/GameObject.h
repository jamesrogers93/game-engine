#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "game-engine/Entity/Entity.h"

class GameObject : public Entity
{
public:
    GameObject(const std::string &name) : Entity(name, Entity::GAME_OBJECT)
    {}
    
    void initialise(){}
    //void update(){}
};

#endif /* _GAMEOBJECT_H */
