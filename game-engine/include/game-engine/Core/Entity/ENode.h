#ifndef _ENODE_H
#define _ENODE_H

// STD
#include <string>
#include <vector>

class Scene;

class ENode
{
    friend class Scene;
    
protected:
    std::string name;
    std::vector<ENode*> children;
    ENode* parent;
    
    ENode(const std::string &name) : name(name) {}
    ~ENode(){}
    
    virtual void attachToEngine() = 0;
    
public:
    const std::vector<ENode*>& getChildren()    {   return this->children;  }
    const ENode* getParent()    {   return this->parent;    }
    
};

#endif /* _ENODE_H */
