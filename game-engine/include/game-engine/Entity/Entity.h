#ifndef _ENODE_H
#define _ENODE_H

// STD
#include <string>
#include <vector>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define MAX_TRANSFORMATIONS 2
class Scene;
class Property;

class Entity
{
    friend class Scene;
private:
    
    static const glm::vec3 DEFAULT_POSITION;
    
public:
    
    //enum Type
    //{
        //
    //};
    //Type type;
    
protected:
    
    std::string name;
    std::vector<Entity*> children;
    std::vector<Property*> properties;
    Entity* parent;
    glm::mat4 localModel;
    glm::mat4 globalModel;
    
    glm::mat4  T[MAX_TRANSFORMATIONS];    // Translate
    glm::mat4  R[MAX_TRANSFORMATIONS];    // Rotate
    glm::mat4  S[MAX_TRANSFORMATIONS];    // Scale
    glm::fquat Q[MAX_TRANSFORMATIONS];    // Quaternion
    
    Entity(const std::string &name);
    ~Entity(){}
    
public:
    
    virtual void initialise() = 0;
    virtual void update() = 0;
    void updateChildren();
    
    const std::string& getName()                 {   return this->name;  }
    const std::vector<Entity*>& getChildren()    {   return this->children;  }
    const std::vector<Property*>& getProperties(){   return this->properties; }
    const Entity* getParent()                    {   return this->parent;    }
    
    const glm::mat4& getLocalModel() { return this->localModel; }
    const glm::mat4& getGlobalModel() { return this->globalModel; }
    
    void addChild(Entity *child);
    
    const void translate(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void translate(const glm::vec3 &p, const unsigned int &order = 0);
    const void scale(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void scale(const glm::vec3 &p, const unsigned int &order = 0);
    const void rotate(const float &a, const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void rotate(const float &a, const glm::vec3 &r, const unsigned int &order = 0);
    const void rotate(const glm::fquat &q, const unsigned int &order = 0);
    
    const void translateOW(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void translateOW(const glm::vec3 &p, const unsigned int &order = 0);
    const void scaleOW(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void scaleOW(const glm::vec3 &p, const unsigned int &order = 0);
    const void rotateOW(const float &a, const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void rotateOW(const float &a, const glm::vec3 &r, const unsigned int &order = 0);
    const void rotateOW(const glm::fquat &q, const unsigned int &order = 0);
    
private:
    
    void updateGlobalModel();
    void updateLocalModel();
    
};

#endif /* _ENODE_H */
