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
    
    virtual void update(Shader *shader);
    
    void addShape(GUIShape *shape) { shapes.push_back(shape); }
    
    virtual void touchDown(const float &x, const float &y);
    virtual void touchMove(const float &x, const float &y);
    virtual void touchUp(const float &x, const float &y);
    
    virtual void setCallBack( std::function<void()> functionPtr, const bool &callbackOnTouchDown,  const bool &callbackOnTouchMove,  const bool &callbackOnTouchUp);
    
protected:
    
    std::function<void()> functionPtr;
    
    bool callbackOnTouchDown;
    bool callbackOnTouchMove;
    bool callbackOnTouchUp;
    
    bool hasTouchDown;
    bool hasTouchMove;
    bool hasTouchUp;
    
    std::vector<GUIShape*> shapes;
};

#endif /* _GUIPROPERTY_H */
