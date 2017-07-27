#ifndef _SCENELOGIC_H
#define _SCENELOGIC_H

class SceneLogic
{
protected:
    SceneLogic()
    {}
    ~SceneLogic()
    {}

    virtual void initalise = 0;
    virtual void update() = 0;
};

#endif /* _SCENELOGIC_H */
