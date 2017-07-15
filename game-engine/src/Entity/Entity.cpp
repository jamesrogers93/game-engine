#include "game-engine/Entity/Entity.h"

// STD
#include <algorithm>

// GLM
#include <glm/gtx/quaternion.hpp>

const glm::vec3 Entity::DEFAULT_POSITION = glm::vec3(0.0);

Entity::Entity(const std::string &name) : name(name), parent(NULL)
{
    // Make name lower case
    std::transform(this->name.begin(), this->name.end(), this->name.begin(), ::tolower);
}

void Entity::addChild(Entity *child)
{
    child->parent = this;
    this->children.push_back(child);
}

void Entity::updateChildren()
{
    for(unsigned int i = 0; i < this->children.size(); i++)
    {
        this->children[i]->updateChildren();
        this->children[i]->update();
    }
}

const void Entity::translate(const float &x, const float &y, const float &z)
{
    translate(glm::vec3(x,y,z));
}

const void Entity::translate(const glm::vec3 &p)
{
    this->T = glm::translate(this->T, p);
    this->updateLocalModel();
    this->position+=p;
}

const void Entity::scale(const float &x, const float &y, const float &z)
{
    scale(glm::vec3(x,y,z));
}

const void Entity::scale(const glm::vec3 &s)
{
    this->S = glm::scale(this->S, s);
    this->updateLocalModel();
}

const void Entity::rotate(const float &a, const float &x, const float &y, const float &z, const unsigned int &order)
{
    rotate(a, glm::vec3(x, y, z), order);
}

const void Entity::rotate(const float &a, const glm::vec3 &r, const unsigned int &order)
{
    glm::quat q = glm::angleAxis(a, r);
    rotate(q, order);
}

const void Entity::rotate(const glm::fquat &q, const unsigned int &order)
{
    if(order > MAX_TRANSFORMATIONS)
    {
        return;
    }
    
    this->Q[order] = this->Q[order] * q;
    this->Q[order] = glm::normalize(this->Q[order]);
    this->R[order] = glm::mat4_cast(this->Q[order]);
    this->updateLocalModel();
}

const void Entity::translateOW(const float &x, const float &y, const float &z)
{
    translateOW(glm::vec3(x,y,z));
}

const void Entity::translateOW(const glm::vec3 &p)
{
    this->T = glm::translate(glm::mat4(), p);
    this->updateLocalModel();
    this->position+=p;
}

const void Entity::scaleOW(const float &x, const float &y, const float &z)
{
    scaleOW(glm::vec3(x,y,z));
}

const void Entity::scaleOW(const glm::vec3 &s)
{
    this->S = glm::scale(glm::mat4(), s);
    this->updateLocalModel();
}

const void Entity::rotateOW(const float &a, const float &x, const float &y, const float &z, const unsigned int &order)
{
    rotateOW(a, glm::vec3(x, y, z), order);
}

const void Entity::rotateOW(const float &a, const glm::vec3 &r, const unsigned int &order)
{
    glm::quat q = glm::angleAxis(a, r);
    rotateOW(q, order);
}

const void Entity::rotateOW(const glm::fquat &q, const unsigned int &order)
{
    if(order > MAX_TRANSFORMATIONS)
    {
        return;
    }
    
    this->Q[order] = q;
    this->Q[order] = glm::normalize(this->Q[order]);
    this->R[order] = glm::mat4_cast(this->Q[order]);
    this->updateLocalModel();
}

void Entity::updateGlobalModel()
{
    if(this->parent != NULL)
    {
        this->globalModel = this->parent->globalModel * this->localModel;
    }
    else
    {
        this->globalModel = this->localModel;
    }
    
    for(auto &child : this->children)
    {
        
        child->updateGlobalModel();
    }
}

void Entity::updateLocalModel()
{
    this->localModel = this->R[1] * this->T * this->R[0] * this->S;
}
