#include "game-engine/Core/Utilities/TextureUtil.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "game-engine/Peripherals/System.h"

Texture::Texture(const Texture &texture) : Texture(new unsigned char[texture.getWidth() * texture.getHeight() * texture.getStride()], texture.getWidth(), texture.getHeight(), texture.getStride())
{
    const unsigned char *copyData = texture.getData();
    unsigned int count = width * height * stride;
    for(unsigned int i = 0; i < count; i++)
    {
        data[i] = copyData[i];
    }
}

Texture::~Texture()
{
    stbi_image_free(data);
}

Texture& Texture::operator=(const Texture &texture)
{
    if(this != &texture)
    {
        stbi_image_free(data);
        
        data = new unsigned char[texture.getWidth() * texture.getHeight() * texture.getStride()];
        width = texture.getWidth();
        height = texture.getHeight();
        stride = texture.getStride();
        
        const unsigned char *copyData = texture.getData();
        unsigned int count = width * height * stride;
        for(unsigned int i = 0; i < count; i++)
        {
            data[i] = copyData[i];
        }
        
    }
    
    return *this;
}

Texture* Texture::loadFromFile(const std::string &file, const bool &flip)
{
    
    stbi_set_flip_vertically_on_load(flip);
    
    std::string path = System::assetsPath + file;
    
    int x;
    int y;
    int n;
    unsigned char *data = stbi_load(path.data(), &x, &y, &n, STBI_default);
    
    if(data == NULL)
    {
        return NULL;
    }

    return new Texture(data, x, y, n);
}
