#ifndef _ENODE_H
#define _ENODE_H

// STD
#include <string>
#include <vector>

// GLM
#include <glm/glm.hpp>

class Scene;

class ENode
{
    friend class Scene;
    
protected:
    std::string name;
    std::vector<ENode*> children;
    ENode* parent;
    glm::vec3 position;
    
    ENode(const std::string &name, glm::vec3 position = DEFAULT_POSITION) : name(name) {}
    ~ENode(){}
    
    virtual void attachToEngine() = 0;
    
public:
    const std::vector<ENode*>& getChildren()    {   return this->children;  }
    const ENode* getParent()    {   return this->parent;    }
    
private:
    static const glm::vec3 DEFAULT_POSITION;
    
};

#endif /* _ENODE_H */
