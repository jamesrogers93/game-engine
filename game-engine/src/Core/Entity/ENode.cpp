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
    this->localModel = this->T * this->R * this->S;
    this->position+=p;
}

const void ENode::scale(const float &x, const float &y, const float &z)
{
    scale(glm::vec3(x,y,z));
}

const void ENode::scale(const glm::vec3 &s)
{
    this->S = glm::scale(this->S, s);
    this->localModel = this->T * this->R * this->S;
}

const void ENode::rotate(const float &a, const float &x, const float &y, const float &z)
{
    rotate(a, glm::vec3(x, y, z));
}

const void ENode::rotate(const float &a, const glm::vec3 &r)
{
    glm::quat q = glm::angleAxis(a, r);
    rotate(q);
}

const void ENode::rotate(const glm::fquat &q)
{
    this->Q = this->Q * q;
    this->Q = glm::normalize(this->Q);
    this->R = glm::mat4_cast(this->Q);
    this->localModel = this->T * this->R * this->S;
}

const void ENode::translateOW(const float &x, const float &y, const float &z)
{
    translateOW(glm::vec3(x,y,z));
}

const void ENode::translateOW(const glm::vec3 &p)
{
    this->T = glm::translate(glm::mat4(), p);
    this->localModel = this->T * this->R * this->S;
    this->position+=p;
}

const void ENode::scaleOW(const float &x, const float &y, const float &z)
{
    scaleOW(glm::vec3(x,y,z));
}

const void ENode::scaleOW(const glm::vec3 &s)
{
    this->S = glm::scale(glm::mat4(), s);
    this->localModel = this->T * this->R * this->S;
}

const void ENode::rotateOW(const float &a, const float &x, const float &y, const float &z)
{
    rotateOW(a, glm::vec3(x, y, z));
}

const void ENode::rotateOW(const float &a, const glm::vec3 &r)
{
    glm::quat q = glm::angleAxis(a, r);
    rotateOW(q);
}

const void ENode::rotateOW(const glm::fquat &q)
{
    this->Q = q;
    this->Q = glm::normalize(this->Q);
    this->R = glm::mat4_cast(this->Q);
    this->localModel = this->T * this->R * this->S;
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
