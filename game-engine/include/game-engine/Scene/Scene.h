#ifndef _SCENE_H
#define _SCENE_H

// STD
#include <string>
#include <vector>

class Entity;
class SceneLogic;

class Scene
{
private:
    std::string name;
    std::vector<Entity*> entities;
    
    bool mHasPrepared;
    
    SceneLogic *mSceneLogic;
    
public:
    
    Scene(std::string name) : name(name), mHasPrepared(false), mSceneLogic(NULL) {}
    ~Scene() {}

    void prepare();
    void unPrepare();

	const std::string& getName();
    
    void addEntity(Entity *entity) {   this->entities.push_back(entity);   }
    
    void setSceneLogic(SceneLogic *sceneLogic) { mSceneLogic = sceneLogic; }

    void update();
    
    void draw();

private:
    void prepare(Entity *);
    void unPrepare(Entity *);
    
    
};

#endif /* _SCENE_H */
