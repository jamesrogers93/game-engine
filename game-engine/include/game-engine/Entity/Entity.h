#ifndef _ENODE_H
#define _ENODE_H

// STD
#include <string>
#include <vector>

// Game Engine Core
#include "game-engine/Core/GL/GLData.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

//#include "game-engine/Entity/EntityObserver.h"

#define MAX_TRANSFORMATIONS 2

class Scene;
class Property;

class Entity
{
    friend class Scene;
private:
    
    static const glm::vec3 DEFAULT_POSITION;
    
public:
    
    enum Type
    {
        JOINT, CAMERA, AR_TRACKER, GAME_OBJECT
    };
    
protected:
    
    Type mType;
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
    
    Entity(const std::string &name, const Type &type);
    ~Entity(){}
    
public:
    
    virtual void initialise() = 0;
    virtual void update();
    //void updateChildren();
    
    const Type& getType() const                         {   return this->mType; }
    const std::string& getName() const                  {   return this->name;  }
    const std::vector<Entity*>& getChildren() const     {   return this->children;  }
    const std::vector<Property*>& getProperties() const {   return this->properties; }
    const Entity* getParent() const                     {   return this->parent;    }
    
    const glm::mat4& getLocalModel() const { return this->localModel; }
    const glm::mat4& getGlobalModel() const { return this->globalModel; }
    
    //UpdateNotification& getLocalTransformUpdate() { return mLocalTransformUpdate; }
    //UpdateNotification& getGlobalTransformUpdate() { return mGlobalTransformUpdate; }
    
    bool hasParent() const { return this->parent != NULL; }
    
    void addChild(Entity *child);
    void addProperty(Property *property);
    
    const void transform(const glm::mat4 &t);
    const void translate(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void translate(const glm::vec3 &p, const unsigned int &order = 0);
    const void scale(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void scale(const glm::vec3 &p, const unsigned int &order = 0);
    const void rotate(const float &a, const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void rotate(const float &a, const glm::vec3 &r, const unsigned int &order = 0);
    const void rotate(const glm::fquat &q, const unsigned int &order = 0);
    
    const void transformOW(const glm::mat4 &t);
    const void translateOW(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void translateOW(const glm::vec3 &p, const unsigned int &order = 0);
    const void scaleOW(const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void scaleOW(const glm::vec3 &p, const unsigned int &order = 0);
    const void rotateOW(const float &a, const float &x, const float &y, const float &z, const unsigned int &order = 0);
    const void rotateOW(const float &a, const glm::vec3 &r, const unsigned int &order = 0);
    const void rotateOW(const glm::fquat &q, const unsigned int &order = 0);
    
    
    const std::string typeToString() const;
    
    //void attachObserver(EntityObserver* observer) { mObservers.push_back(observer); }
    
private:
    
    void updateGlobalModel();
    void updateLocalModel();
    
    //UpdateNotification mLocalTransformUpdate;
    //UpdateNotification mGlobalTransformUpdate;
    
    //std::vector<EntityObserver*> mObservers;
    
};

#endif /* _ENODE_H */
