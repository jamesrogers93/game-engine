#ifndef _SCENE_H
#define _SCENE_H

// STD
#include <string>
#include <vector>

class Entity;

class Scene
{
private:
    std::string name;
    std::vector<Entity*> entities;
    
    bool mHasPrepared;
    
public:
    
    Scene(std::string name) : name(name), mHasPrepared(false) {}
    ~Scene() {}

    void prepare();
    void unPrepare();

	const std::string& getName();
    
    void addEntity(Entity *entity) {   this->entities.push_back(entity);   }

    void update();

private:
    void prepare(Entity *);
    void unPrepare(Entity *);
    
    
};

#endif /* _SCENE_H */
