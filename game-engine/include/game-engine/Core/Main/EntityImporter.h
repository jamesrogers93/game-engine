#ifndef _ENTITYIMPORTER_H
#define _ENTITYIMPORTER_H

#include <fstream>
#include <map>

#include "game-engine/Core/Utilities/JMPImporter.h"

#include "game-engine/Core/Main/Entity.h"

class EntityImporter : public JMPImporter<Entity>
{
private:
    
    static const std::string JOINT_TYPE;
    
    std::map<std::string, Entity*> importedEntites; // For assigning entity children
    
public:
    EntityImporter() : JMPImporter()
    {}
    
    void ImportAsynchronously(const std::string &path);
    bool Import(const std::string &path);
    
    void myTest(std::string t) {}
    
    void readJoint(std::ifstream &file);
};

#endif /* _ENTITYIMPORTER_H */
