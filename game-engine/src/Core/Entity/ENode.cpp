#include "game-engine/Core/Entity/ENode.h"

const glm::vec3 ENode::DEFAULT_POSITION = glm::vec3(0.0);

void ENode::addChild(ENode *child)
{
    child->parent = this;
    this->children.push_back(child);
}

const void ENode::translate(const glm::vec3 &p)
{
    this->localModel = glm::translate(this->localModel, p);
}

const void ENode::translate(const float &x, const float &y, const float &z)
{
    this->localModel = glm::translate(this->localModel, glm::vec3(x,y,z));
}

const void ENode::scale(const glm::vec3 &s)
{
    this->localModel = glm::scale(this->localModel, s);
}

const void ENode::scale(const float &x, const float &y, const float &z)
{
    this->localModel = glm::scale(this->localModel, glm::vec3(x,y,z));
}

const void ENode::rotate(const float &a, const glm::vec3 &r)
{
    this->localModel = glm::rotate(this->localModel, a, r);
}

const void ENode::rotate(const float &a, const float &x, const float &y, const float &z)
{
    this->localModel = glm::rotate(this->localModel, a, glm::vec3(x,y,z));
}

void ENode::updateGlobalModel()
{
    if(this->parent != NULL)
    {
        this->globalModel = this->parent->globalModel * this->localModel;
    }
    
    for(auto &child : this->children)
    {
        child->updateGlobalModel();
    }
}
