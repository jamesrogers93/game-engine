#ifndef _ENODE_H
#define _ENODE_H

// STD
#include <string>
#include <vector>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Scene;

class ENode
{
    friend class Scene;
    
protected:
    std::string name;
    std::vector<ENode*> children;
    ENode* parent;
    glm::mat4 localModel;
    glm::mat4 globalModel;
    
    ENode(const std::string &name, glm::vec3 position = DEFAULT_POSITION) : name(name), parent(NULL)
    {
        this->translate(position);
    }
    ~ENode(){}
    
    virtual void attachToEngine() = 0;
    
public:
    const std::vector<ENode*>& getChildren()    {   return this->children;  }
    const ENode* getParent()    {   return this->parent;    }
    
    void addChild(ENode *child);
    
    const void translate(const glm::vec3 &p);
    const void translate(const float &x, const float &y, const float &z);
    const void scale(const glm::vec3 &p);
    const void scale(const float &x, const float &y, const float &z);
    const void rotate(const float &a, const glm::vec3 &r);
    const void rotate(const float &a, const float &x, const float &y, const float &z);
    
private:
    static const glm::vec3 DEFAULT_POSITION;
    
     void updateGlobalModel();
    
};

#endif /* _ENODE_H */
