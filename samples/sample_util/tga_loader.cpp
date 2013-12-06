#include "tga_loader.hpp"

#include <climits>
#include <iostream>
#include <fstream>

namespace sample_util
{
    struct tga_header
    {
        unsigned char id_size;
        unsigned char map_type;
        unsigned char image_type;
        unsigned short palette_start;
        unsigned short palette_size;
        unsigned char palette_entry_depth;
        unsigned short x;
        unsigned short y;
        unsigned short width;
        unsigned short height;
        unsigned char color_depth;
        unsigned char descriptor;
    };

    #define INVERTED_BIT (1 << 5)

    template <typename data_type>
    void read_binary(std::ifstream& stream, data_type& item)
    {
        stream.read(reinterpret_cast<char *>(&item), sizeof(data_type));
    }

    template <typename data_type>
    void read_binary(std::ifstream& stream, std::vector<data_type>& items)
    {
        stream.read(reinterpret_cast<char *>(items.data()), sizeof(data_type) * items.size());
    }

    tga_image load_tga_image_from_file(const std::string& path)
    {
        std::ifstream stream(path, std::ios::binary);

        tga_header header;
        read_binary(stream, header.id_size);
        read_binary(stream, header.map_type);
        read_binary(stream, header.image_type);
        read_binary(stream, header.palette_start);
        read_binary(stream, header.palette_size);
        read_binary(stream, header.palette_entry_depth);
        read_binary(stream, header.x);
        read_binary(stream, header.y);
        read_binary(stream, header.width);
        read_binary(stream, header.height);
        read_binary(stream, header.color_depth);
        read_binary(stream, header.descriptor);

        tga_image image;
        image.width = header.width;
        image.height = header.height;

        size_t pixel_component_count = header.color_depth / CHAR_BIT;
        std::vector<unsigned char> buffer(header.width * header.height * pixel_component_count);
        read_binary(stream, buffer);

        for (size_t y = 0; y < header.height; y++)
        {
            size_t row_idx = ((header.descriptor & INVERTED_BIT) ? (header.height - 1 - y) : y) * header.width * pixel_component_count;
            for (size_t x = 0; x < header.width; x++)
            {
                size_t pixel_idx = row_idx + x * pixel_component_count;
                pixel pix =
                {
                    (pixel_component_count > 0) ? buffer[pixel_idx + 0] : 0,
                    (pixel_component_count > 1) ? buffer[pixel_idx + 1] : 0,
                    (pixel_component_count > 2) ? buffer[pixel_idx + 2] : 0,
                    (pixel_component_count > 3) ? buffer[pixel_idx + 3] : 255,
                };
                image.data.push_back(pix);
            }
        }

        return image;
    }
}
