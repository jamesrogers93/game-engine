#ifndef _GUIPROPERTY_H
#define _GUIPROPERTY_H

// STD
#include <string>
#include <vector>

#include "game-engine/Core/Main/Property.h"

#include "game-engine/Modules/GUI/GUIShape.h"

class Shader;

class GUIProperty : public Property
{
public:
    
    bool isTouchable;
    
    GUIProperty(const std::string &name);
    ~GUIProperty();
    
    bool makeActive();
    bool makeUnactive();
    
    virtual void update(Shader *shader);
    
    void addShape(GUIShape *shape) { shapes.push_back(shape); }
    
    virtual void touchDown(const float &x, const float &y);
    virtual void touchMove(const float &x, const float &y);
    virtual void touchUp(const float &x, const float &y);
    
    void setCallbackOnTouchDown(std::function<void()> callback);
    void setCallbackOnTouchMove(std::function<void()> callback);
    void setCallbackOnTouchUp(std::function<void()> callback);
    
    void removeCallbackOnTouchDown() { callbackOnTouchDownFlag = false; }
    void removeCallbackOnTouchMove() { callbackOnTouchMoveFlag = false; }
    void removeCallbackOnTouchUp() { callbackOnTouchUpFlag = false; }
protected:
    
    std::function<void()> callbackOnTouchDown;
    std::function<void()> callbackOnTouchMove;
    std::function<void()> callbackOnTouchUp;
    
    bool callbackOnTouchDownFlag;
    bool callbackOnTouchMoveFlag;
    bool callbackOnTouchUpFlag;
    
    bool hasTouchDown;
    bool hasTouchMove;
    bool hasTouchUp;
    
    std::vector<GUIShape*> shapes;
};

#endif /* _GUIPROPERTY_H */
