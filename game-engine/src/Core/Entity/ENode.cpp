#include "game-engine/Core/Entity/ENode.h"

// STD
#include <algorithm>

// GLM
#include <glm/gtx/quaternion.hpp>

const glm::vec3 ENode::DEFAULT_POSITION = glm::vec3(0.0);

ENode::ENode(const std::string &name, glm::vec3 position) : name(name), parent(NULL)
{
    // Make name lower case
    std::transform(this->name.begin(), this->name.end(), this->name.begin(), ::tolower);
    
    // Create the translation matrix from position
    this->translate(position);
}

void ENode::addChild(ENode *child)
{
    child->parent = this;
    this->children.push_back(child);
}

void ENode::updateChildren()
{
    for(unsigned int i = 0; i < this->children.size(); i++)
    {
        this->children[i]->updateChildren();
        this->children[i]->update();
    }
}

const void ENode::translate(const float &x, const float &y, const float &z)
{
    translate(glm::vec3(x,y,z));
}

const void ENode::translate(const glm::vec3 &p)
{
    this->T = glm::translate(this->T, p);
    this->updateLocalModel();
    this->position+=p;
}

const void ENode::scale(const float &x, const float &y, const float &z)
{
    scale(glm::vec3(x,y,z));
}

const void ENode::scale(const glm::vec3 &s)
{
    this->S = glm::scale(this->S, s);
    this->updateLocalModel();
}

const void ENode::rotate(const float &a, const float &x, const float &y, const float &z, const unsigned int &order)
{
    rotate(a, glm::vec3(x, y, z), order);
}

const void ENode::rotate(const float &a, const glm::vec3 &r, const unsigned int &order)
{
    glm::quat q = glm::angleAxis(a, r);
    rotate(q, order);
}

const void ENode::rotate(const glm::fquat &q, const unsigned int &order)
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

const void ENode::translateOW(const float &x, const float &y, const float &z)
{
    translateOW(glm::vec3(x,y,z));
}

const void ENode::translateOW(const glm::vec3 &p)
{
    this->T = glm::translate(glm::mat4(), p);
    this->updateLocalModel();
    this->position+=p;
}

const void ENode::scaleOW(const float &x, const float &y, const float &z)
{
    scaleOW(glm::vec3(x,y,z));
}

const void ENode::scaleOW(const glm::vec3 &s)
{
    this->S = glm::scale(glm::mat4(), s);
    this->updateLocalModel();
}

const void ENode::rotateOW(const float &a, const float &x, const float &y, const float &z, const unsigned int &order)
{
    rotateOW(a, glm::vec3(x, y, z), order);
}

const void ENode::rotateOW(const float &a, const glm::vec3 &r, const unsigned int &order)
{
    glm::quat q = glm::angleAxis(a, r);
    rotateOW(q, order);
}

const void ENode::rotateOW(const glm::fquat &q, const unsigned int &order)
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

void ENode::updateGlobalModel()
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

void ENode::updateLocalModel()
{
    this->localModel = this->R[1] * this->T * this->R[0] * this->S;
}
