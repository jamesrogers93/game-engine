#ifndef _ENODE_H
#define _ENODE_H

// STD
#include <string>
#include <vector>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Scene;

class ENode
{
    friend class Scene;
private:
    
    static const glm::vec3 DEFAULT_POSITION;
    
protected:
    std::string name;
    std::vector<ENode*> children;
    ENode* parent;
    glm::vec3 position;
public:
    glm::mat4 localModel;   // MAKE PROTECTED!!!
protected:
    glm::mat4 globalModel;
    
    glm::mat4  T;    // Translate
    glm::mat4  R;    // Rotate
    glm::mat4  S;    // Scale
    glm::fquat Q;    // Quaternion
    
    ENode(const std::string &name, glm::vec3 position = DEFAULT_POSITION);
    ~ENode(){}
    
public:
    
    virtual void initialise() = 0;
    virtual void update() = 0;
    void updateChildren();
    
    const std::vector<ENode*>& getChildren()    {   return this->children;  }
    const ENode* getParent()    {   return this->parent;    }
    
    void addChild(ENode *child);
    
    const void translate(const float &x, const float &y, const float &z);
    const void translate(const glm::vec3 &p);
    const void scale(const float &x, const float &y, const float &z);
    const void scale(const glm::vec3 &p);
    const void rotate(const float &a, const float &x, const float &y, const float &z);
    const void rotate(const float &a, const glm::vec3 &r);
    const void rotate(const glm::fquat &q);
    
    const void translateOW(const float &x, const float &y, const float &z);
    const void translateOW(const glm::vec3 &p);
    const void scaleOW(const float &x, const float &y, const float &z);
    const void scaleOW(const glm::vec3 &p);
    const void rotateOW(const float &a, const float &x, const float &y, const float &z);
    const void rotateOW(const float &a, const glm::vec3 &r);
    const void rotateOW(const glm::fquat &q);
    
private:
    
    void updateGlobalModel();
    
};

#endif /* _ENODE_H */
