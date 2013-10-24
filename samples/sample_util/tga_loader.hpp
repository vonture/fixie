#ifndef _TGA_LOADER_HPP_
#define _TGA_LOADER_HPP_

#include <array>
#include <vector>

typedef std::array<unsigned char, 4> pixel;

struct tga_image
{
    size_t width;
    size_t height;
    std::vector<pixel> data;
};

tga_image load_tga_image_from_file(const std::string& path);

#endif // _TGA_LOADER_HPP_
