#ifndef _SCENELOGIC_H
#define _SCENELOGIC_H

class Scene;

class SceneLogic
{
    friend class Scene;
    
protected:
    
    Scene* mScene;
    
    SceneLogic(Scene *scene) : mScene(scene)
    {}
    ~SceneLogic()
    {}
    
    virtual void initialise() = 0;
    virtual void deinitialise() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

};

#endif /* _SCENELOGIC_H */
