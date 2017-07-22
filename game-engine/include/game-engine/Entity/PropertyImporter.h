#ifndef _PROPERTYIMPORTER_H
#define _PROPERTYIMPORTER_H

#include <fstream>

#include "game-engine/JMPImporter.h"

#include "game-engine/Entity/Property.h"

class PropertyImporter : public JMPImporter<Property>
{
private:
    
    static const std::string MESH_TYPE;
    static const std::string ANIMATABLE_MESH_TYPE;
    
public:
    PropertyImporter() : JMPImporter()
    {}
    
    bool Import(const std::string &path);
    
    void readMeshProperty(std::ifstream &file);
    void readAnimatableMeshProperty(std::ifstream &file);
};

#endif /* _PROPERTYIMPORTER_H */
