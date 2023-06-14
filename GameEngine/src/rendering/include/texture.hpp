#pragma once

#include <glad/gl.h>
#include <string>

class Texture
{
public:
    Texture(GLenum textureTarget, const std::string &fileName);
    ~Texture();

    // Should be called once to load the texture
    bool load();
    // Must be called at least once for the specific texture unit
    void bind(GLenum textureUnit);

private:
    void loadInternal(void *image_data);

    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    int m_imageWidth = 0;
    int m_imageHeight = 0;
    int m_imageBPP = 0;
};