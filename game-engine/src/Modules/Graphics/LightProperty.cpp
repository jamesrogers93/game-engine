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

void LightProperty::initialise()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addLightProperty(this->mName, this);
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

