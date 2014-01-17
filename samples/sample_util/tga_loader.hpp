#ifndef _SAMPLE_UTIL_TGA_LOADER_HPP_
#define _SAMPLE_UTIL_TGA_LOADER_HPP_

#include <array>
#include <vector>

namespace sample_util
{
    typedef std::array<unsigned char, 4> pixel;

    struct tga_image
    {
        size_t width;
        size_t height;
        std::vector<pixel> data;
    };

    tga_image load_tga_image_from_file(const std::string& path);
}

#endif // _SAMPLE_UTIL_TGA_LOADER_HPP_
