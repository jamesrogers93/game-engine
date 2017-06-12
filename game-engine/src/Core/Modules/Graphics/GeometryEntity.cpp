#include "game-engine/Core/Modules/Graphics/GeometryEntity.h"

#include "game-engine/Core/Modules/Graphics/Graphics.h"

void GeometryEntity::attachToEngine()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addGeometryEntity(this->name, this);
}
