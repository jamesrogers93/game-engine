#ifndef _PROPERTY_H
#define _PROPERTY_H

#include <string>
class Entity;

class Property
{
public:
    enum Type
    {
        MESH, ANIMATABLE_MESH, DIRECTIONAL_LIGHT, POINT_LIGHT, ANIMATOR, GUI
    };
private:
    static const bool DEFAULT_ACTIVE;
    
protected:
    std::string mName;
    Type mType;
    
    Entity *mOwner;
    
    bool mActive;
    
public:
    Property(const std::string &name, const Type &type);
    
    void setName(const std::string &name) { mName = name; }
    void setOwner(Entity *owner);
    
    const std::string& getName() const { return this->mName; }
    const Type& getType() const { return this->mType; }
    const Entity* getOwner() const { return this->mOwner; }
    
    const std::string typeToString() const;
    
    virtual bool makeActive() { this->mActive = true; return true; }
    virtual bool makeUnactive() { this->mActive = false; return true; }
};

#endif /* _PROPERTY_H */
