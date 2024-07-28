#include <algorithm>
#include <cmath>
#include <glad/glad.h>

#include "AiryEngineCore/Log.hpp"

#include "Texture2D.hpp"

namespace AiryEngine
{
    Texture2D::Texture2D(const unsigned char* pixels, const unsigned int width, const unsigned int height, const unsigned int channels)
        : width(width)
        , height(height)
        , pixels(pixels)
    {
        if (4 == channels) this->format = GL_RGBA;
        else if (3 == channels) this->format = GL_RGB;
        else 
        {
            LOG_CRITICAL("Invalid number of channels in texture format: {}", channels);
            return;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &this->id);
        const GLsizei mip_levels = static_cast<GLsizei>(std::log2(std::max(this->width, this->height))) + 1;
        glTextureStorage2D(this->id, mip_levels, GL_RGB8, this->width, this->height);
        glTextureSubImage2D(this->id, 0, this->x_offset, this->y_offset, this->width, this->height, this->format, GL_UNSIGNED_BYTE, this->pixels);
        glTextureParameteri(this->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(this->id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(this->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(this->id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateTextureMipmap(this->id);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &this->id);
    }

    Texture2D& Texture2D::operator=(Texture2D&& texture) noexcept
    {
        glDeleteTextures(1, &this->id);
        this->id = texture.id;
        this->width = texture.width;
        this->height = texture.height;
        this->format = texture.format;
        this->x_offset = texture.x_offset;
        this->y_offset = texture.y_offset;
        this->pixels = texture.pixels;
        texture.id = 0;
        //texture.pixels = nullptr;
        return *this;
    }

    Texture2D::Texture2D(Texture2D&& texture) noexcept
    {
        this->id = texture.id;
        this->width = texture.width;
        this->height = texture.height;
        this->format = texture.format;
        this->x_offset = texture.x_offset;
        this->y_offset = texture.y_offset;
        this->pixels = texture.pixels;
        texture.id = 0;
        //texture.pixels = nullptr;
    }

    void Texture2D::bind(const unsigned int unit) const
    {
        glBindTextureUnit(unit, this->id);
    }
}