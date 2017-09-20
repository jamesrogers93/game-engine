#ifndef _MATERIALIMPORTER_H
#define _MATERIALIMPORTER_H

#include "game-engine/Core/Utilities/JMPImporter.h"

class Material;

class MaterialImporter : public JMPImporter<Material>
{
public:
    MaterialImporter() : JMPImporter()
    {}
    
    void ImportAsynchronously(const std::string &path);
    bool Import(const std::string &path);
};

#endif /* _MATERIALIMPORTER_H */
