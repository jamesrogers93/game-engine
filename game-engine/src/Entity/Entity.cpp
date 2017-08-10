#include "game-engine/Entity/Entity.h"

// STD
#include <algorithm>

// GLM
#include <glm/gtx/quaternion.hpp>

#include "game-engine/Entity/Property.h"

const glm::vec3 Entity::DEFAULT_POSITION = glm::vec3(0.0);

Entity::Entity(const std::string &name, const Type &type) :  mType(type), name(name), parent(NULL)
{
    // Make name lower case
    std::transform(this->name.begin(), this->name.end(), this->name.begin(), ::tolower);
}

void Entity::addChild(Entity *child)
{
    child->parent = this;
    child->updateGlobalModel();
    this->children.push_back(child);
}

void Entity::addProperty(Property *property)
{
    property->setOwner(this);
    this->properties.push_back(property);
}

const Property* Entity::getProperty(const std::string &name)
{
    for(auto property : properties)
    {
        if(name == property->getName())
        {
            return property;
        }
    }
    
    return NULL;
}

void Entity::update()
{
    for(unsigned int i = 0; i < this->children.size(); i++)
    {
        this->children[i]->update();
    }
}

const void Entity::transform(const glm::mat4 &t)
{
    this->localModel = t;
}

const void Entity::translate(const float &x, const float &y, const float &z, const unsigned int &order)
{
    translate(glm::vec3(x,y,z), order);
}

const void Entity::translate(const glm::vec3 &p, const unsigned int &order)
{
    this->T[order] = glm::translate(this->T[order], p);
    this->updateLocalModel();
}

const void Entity::translateLocalAxis(const float &x, const float &y, const float &z, const unsigned int &order)
{
    translateLocalAxis(glm::vec3(x,y,z), order);
}

const void Entity::translateLocalAxis(const glm::vec3 &p, const unsigned int &order)
{
    glm::mat4 test = R[order] * glm::translate(glm::mat4(), p);
    this->T[order] = glm::translate(this->T[order], glm::vec3(test[3]));
    this->updateLocalModel();
}

const void Entity::scale(const float &x, const float &y, const float &z, const unsigned int &order)
{
    scale(glm::vec3(x,y,z), order);
}

const void Entity::scale(const glm::vec3 &s, const unsigned int &order)
{
    this->S[order] = glm::scale(this->S[order], s);
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

const void Entity::transformOW(const glm::mat4 &t)
{
    this->localModel = t;
}

const void Entity::translateOW(const float &x, const float &y, const float &z, const unsigned int &order)
{
    translateOW(glm::vec3(x,y,z), order);
}

const void Entity::translateOW(const glm::vec3 &p, const unsigned int &order)
{
    this->T[order] = glm::translate(glm::mat4(), p);
    this->updateLocalModel();
}

const void Entity::scaleOW(const float &x, const float &y, const float &z, const unsigned int &order)
{
    scaleOW(glm::vec3(x,y,z), order);
}

const void Entity::scaleOW(const glm::vec3 &s, const unsigned int &order)
{
    this->S[order] = glm::scale(glm::mat4(), s);
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

const std::string Entity::typeToString() const
{
    switch(this->mType)
    {
        case Entity::JOINT:
            return "joint";
        case Entity::AR_TRACKER:
            return "artracker";
        case Entity::CAMERA:
            return "camera";
        default:
            return "";
    }
}
void Entity::updateGlobalModel()
{
    if(this->parent != NULL)
    {
        
        //if(this->parent->getGlobalTransformUpdate().getFlag() || this->getLocalTransformUpdate().getFlag())
        //{
            this->globalModel = this->parent->globalModel * this->localModel;
        //    this->mGlobalTransformUpdate.notify();
        //}
        
    }
    else
    {
        //if(this->getLocalTransformUpdate().getFlag())
        //{
            this->globalModel = this->localModel;
        //    this->mGlobalTransformUpdate.notify();
        //}
    }
    
    for(auto &child : this->children)
    {
        
        child->updateGlobalModel();
    }
}

void Entity::updateLocalModel()
{
    
    /*glm::mat4 model;
    
    for(unsigned int i = 0; i < MAX_TRANSFORMATIONS; i++)
    {
        model = model * this->T[i] * this->R[i] * this->S[i];
    }
    
    this->localModel = model;*/
    
    this->localModel = this->T[1] * this->R[1] * this->S[1] * this->T[0] * this->R[0] * this->S[0];
    updateGlobalModel();
    //mLocalTransformUpdate.notify();
}
