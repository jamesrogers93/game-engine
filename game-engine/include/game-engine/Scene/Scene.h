#ifndef _SCENE_H
#define _SCENE_H

// STD
#include <string>
#include <vector>

class Entity;
class SceneLogic;

class Scene
{
    friend class SceneLogic;
    
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
    void prepare(Entity *);
    void unPrepare(Entity *);

	const std::string& getName();
    
    void addEntity(Entity *entity) {   this->entities.push_back(entity);   }
    void removeEntity(const std::string &name);
    Entity* getEntity(const std::string &name);
    
    SceneLogic* getSceneLogic() { return mSceneLogic; }
    void setSceneLogic(SceneLogic *sceneLogic) { mSceneLogic = sceneLogic; }

    void update();
    
    void draw();
    
};

#endif /* _SCENE_H */
