#ifndef _MESHIMPORTER_H
#define _MESHIMPORTER_H

#include <fstream>

#include "game-engine/JMPImporter.h"

class Mesh;

class MeshImporter : public JMPImporter<Mesh>
{
public:
    MeshImporter() : JMPImporter()
    {}
    
    void ImportAsynchronously(const std::string &path);
    bool Import(const std::string &path);
    
private:
    
    void readMesh(std::ifstream &file);
};

#endif /* _MESHIMPORTER_H */
