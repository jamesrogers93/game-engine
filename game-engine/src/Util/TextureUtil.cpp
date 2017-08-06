#include "game-engine/Util/TextureUtil.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "game-engine/Device/System.h"

bool Texture::loadFromFile(Texture &texture, const std::string &file)
{
    
    std::string path = System::assetsPath + file;
    
    int x;
    int y;
    int n;
    unsigned char *data = stbi_load(path.data(), &x, &y, &n, 0);
    
    if(data == NULL)
    {
        return false;
    }
    
    texture = Texture(data, x, y, n);
    
    return true;
}
