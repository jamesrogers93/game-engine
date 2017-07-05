#ifndef _SCENE_H
#define _SCENE_H

// STD
#include <string>
#include <vector>

class ENode;

class Scene
{
public:
    
    Scene(std::string name) : name(name) {}
    ~Scene() {}

    void deinitalise(){}

	const std::string& getName();
    
    void addEntity(ENode *entity) {   this->entities.push_back(entity);   }

    void update();
//protected:

private:
	std::string name;
    std::vector<ENode*> entities;
};

#endif /* _SCENE_H */
