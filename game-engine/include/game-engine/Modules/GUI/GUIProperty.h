#ifndef _GUIPROPERTY_H
#define _GUIPROPERTY_H

// STD
#include <string>
#include <vector>

#include "game-engine/Entity/Property.h"

#include "game-engine/Modules/GUI/GUIShape.h"

class Shader;

class GUIProperty : public Property
{
public:
    
    GUIProperty(const std::string &name);
    
    bool makeActive();
    bool makeUnactive();
    
    void update(Shader *shader);
    
private:
    
    std::vector<GUIShape*> shapes;
};

#endif /* _GUIPROPERTY_H */
