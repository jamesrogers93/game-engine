#include "game-engine/Modules/Graphics/LightProperty.h"

// Game Engine Core
#include "game-engine/Modules/Graphics/Graphics.h"

const std::string LightProperty::SHADER_AMBIENT_NAME = "].ambient";
const std::string LightProperty::SHADER_DIFFUSE_NAME = "].diffuse";
const std::string LightProperty::SHADER_SPECULAR_NAME = "].specular";

const bool LightProperty::DEFAULT_ON = true;

LightProperty::Type LightProperty::getType() const
{
    return this->type;
}

/*void LightProperty::initialise()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addLightProperty(this->mName, this);
}*/

bool LightProperty::makeActive()
{
    Property::makeActive();
    
    Graphics *g = &Graphics::getInstance();
    
    return g->addLightProperty(this->mName, this);
}

bool LightProperty::makeUnactive()
{
    Property::makeUnactive();
    
    Graphics *g = &Graphics::getInstance();
    
    return g->removeLightProperty(this->mName);
}

void LightProperty::turnOn()
{
    this->on = true;
}

void LightProperty::turnOff()
{
    this->on = false;
}

const bool& LightProperty::isOn()
{
    return this->on;
}

