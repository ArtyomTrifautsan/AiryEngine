#pragma once


namespace AiryEngine {

    class Texture2D 
    {
    public:
        Texture2D(const unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int channels);
        ~Texture2D();

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&& texture) noexcept;
        Texture2D(Texture2D&& texture) noexcept;

        void bind(const unsigned int unit) const;

    private:
        unsigned int id = 0;
        unsigned int width = 0;
        unsigned int height = 0;
        unsigned int format;
        int x_offset = 0;
        int y_offset = 0;
        const unsigned char* pixels = nullptr;
    };

}