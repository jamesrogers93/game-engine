#ifndef _MATERIALIMPORTER_H
#define _MATERIALIMPORTER_H

#include "game-engine/JMPImporter.h"

class Material;

class MaterialImporter : public JMPImporter<Material>
{
public:
    MaterialImporter() : JMPImporter()
    {}
    
    bool Import(const std::string &path);
};

#endif /* _MATERIALIMPORTER_H */
