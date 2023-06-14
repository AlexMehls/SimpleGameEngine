#include "texture.hpp"

#include <stb_image.h>
#include <iostream>

Texture::Texture(GLenum textureTarget, const std::string &fileName)
{
    m_textureTarget = textureTarget;
    m_fileName = fileName;
}

Texture::~Texture()
{
    if (m_textureObj != GL_INVALID_VALUE)
    {
        glDeleteTextures(1, &m_textureObj);
    }
}

bool Texture::load()
{
    stbi_set_flip_vertically_on_load(1);

    unsigned char *image_data = stbi_load(m_fileName.c_str(), &m_imageWidth, &m_imageHeight, &m_imageBPP, 0);

    if (!image_data)
    {
        std::cerr << "Can't load texture from " << m_fileName << " - " << stbi_failure_reason() << std::endl;
        return false;
    }
    std::cout << "Width " << m_imageWidth << ", Height " << m_imageHeight << ", BPP " << m_imageBPP << std::endl;

    loadInternal(image_data);
    stbi_image_free(image_data);

    return true;
}

void Texture::loadInternal(void *image_data)
{
    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);

    if (m_textureTarget == GL_TEXTURE_2D)
    {
        switch (m_imageBPP)
        {
        case 1:
            glTexImage2D(m_textureTarget, 0, GL_RED, m_imageWidth, m_imageHeight, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
            break;

        case 3:
            glTexImage2D(m_textureTarget, 0, GL_RGB, m_imageWidth, m_imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
            break;

        case 4:
            glTexImage2D(m_textureTarget, 0, GL_RGBA, m_imageWidth, m_imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
            break;

        default:
            break;
        }
    }
    else
    {
        std::cerr << "Support for texture target " << m_textureTarget << " is not implemented" << std::endl;
        exit(1);
    }

    glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_BASE_LEVEL, 0);

    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(m_textureTarget);

    glBindTexture(m_textureTarget, 0);
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}
