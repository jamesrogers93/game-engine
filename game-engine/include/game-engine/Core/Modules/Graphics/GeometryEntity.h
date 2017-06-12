#ifndef _GRAPHICSENTITY_H
#define _GRAPHICSENTITY_H

// STD
#include <string>

// Game Engine Core
#include "game-engine/Core/Entity/ENode.h"

class GeometryEntity : public ENode
{
public:
    GeometryEntity(const std::string &name, const std::string &geometryKey, const std::string &materialKey)
    : ENode(name), geometry(geometryKey), material(materialKey)
    {}
    
    ~GeometryEntity(){}
    
    const std::string& getGeometryKey() {   return this->geometry;  }
    const std::string& getMaterialKey() {   return this->material;  }
    
private:
    std::string geometry;   // Key to geometry in Graphics
    std::string material;   // Key to material in Graphics
    
    void attachToEngine();
};

#endif /* _GRAPHICSENTITY_H */
