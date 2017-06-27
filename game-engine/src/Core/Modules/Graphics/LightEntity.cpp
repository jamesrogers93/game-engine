#include "game-engine/Core/Modules/Graphics/LightEntity.h"

// Game Engine Core
#include "game-engine/Core/Modules/Graphics/Graphics.h"

const std::string LightEntity::SHADER_AMBIENT_NAME = "].ambient";
const std::string LightEntity::SHADER_DIFFUSE_NAME = "].diffuse";
const std::string LightEntity::SHADER_SPECULAR_NAME = "].specular";

const bool LightEntity::DEFAULT_ON = true;

LightEntity::Type LightEntity::getType() const
{
    return this->type;
}

void LightEntity::attachToEngine()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addLightEntity(this->name, this);
}

void LightEntity::turnOn()
{
    this->on = true;
}

void LightEntity::turnOff()
{
    this->on = false;
}

const bool& LightEntity::isOn()
{
    return this->on;
}

