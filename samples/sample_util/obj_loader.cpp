#include "obj_loader.hpp"

#include <fstream>
#include <sstream>

namespace sample_util
    {
    static bool begins_with(const std::string& input, const std::string& search_string)
    {
        if (input.size() < search_string.size())
        {
            return false;
        }

        for (size_t i = 0; i < search_string.size(); ++i)
        {
            if (input[i] != search_string[i])
            {
                return false;
            }
        }

        return true;
    }

    template <typename vertex_type, typename output_iterator>
    static void copy_face_elements(const std::vector<vertex_type>& source, const std::vector<size_t>& indices, output_iterator output)
    {
        for (size_t i = 0; i < indices.size(); ++i)
        {
            if (indices[i] < 1 || indices[i] > source.size())
            {
                std::ostringstream err;
                err << "index " << i << "(" << indices[i] << ") is out of range, must be in [0, " << source.size() << "].";
                throw std::runtime_error(err.str());
            }
            *output = source[indices[i] - 1];
            ++output;
        }
    }

    template <typename vertex_type, size_t element_count>
    static void compute_bounds(const std::vector< std::array<vertex_type, element_count> >& elements,
                               std::array<vertex_type, element_count>& min_bound, std::array<vertex_type, element_count>& max_bound)
    {
        min_bound.assign(std::numeric_limits<vertex_type>::max());
        max_bound.assign(std::numeric_limits<vertex_type>::min());
        for (size_t i = 0; i < elements.size(); ++i)
        {
            for (size_t j = 0; j < element_count; ++j)
            {
                min_bound[j] = std::min(min_bound[j], elements[i][j]);
                max_bound[j] = std::max(max_bound[j], elements[i][j]);
            }
        }
    }

    template <typename element_type>
    void read_attribute(std::istringstream& stream, element_type& element)
    {
        stream >> element;
    }

    template <typename element_type, size_t count>
    void read_attribute(std::istringstream& stream, std::array<element_type, count>& arr, size_t seperator_size = 0)
    {
        for (size_t i = 0; i < count; ++i)
        {
            stream >> arr[i];
            if (seperator_size > 0 && i + 1 < count)
            {
                char sep;
                for (size_t j = 0; j < seperator_size; ++j)
                {
                    stream >> sep;
                }
            }
        }
    }

    model load_model_from_file(const std::string& path)
    {
        static const std::string vertex_identifier = "v";
        static const std::string texcoord_identifier = "vt";
        static const std::string normal_identifier = "vn";
        static const std::string face_identifier = "f";

        std::vector<float4> vertices;
        std::vector<size_t> vertex_indicies;

        std::vector<float3> texcoords;
        std::vector<size_t> texcoord_indices;

        std::vector<float3> normals;
        std::vector<size_t> normal_indices;

        std::ifstream input_stream(path);
        if (!input_stream)
        {
            std::ostringstream err;
            err << "error opening model file " << path << " for reading.";
            throw std::runtime_error(err.str());
        }

        size_t line_count = 0;
        std::string line, identifier;
        while (std::getline(input_stream, line))
        {
            std::istringstream line_stream(line);
            line_stream >> identifier;

            if (identifier == vertex_identifier)
            {
                float4 vertex = { 0.0f, 0.0f, 0.0f, 1.0f };
                read_attribute(line_stream, vertex);
                vertices.push_back(vertex);
            }
            else if (identifier == texcoord_identifier)
            {
                float3 texcoord = { 0.0f, 0.0f, 0.0f };
                read_attribute(line_stream, texcoord);
                texcoords.push_back(texcoord);
            }
            else if (identifier == normal_identifier)
            {
                float3 normal = { 0.0f, 0.0f, 0.0f };
                read_attribute(line_stream, normal);
                normals.push_back(normal);
            }
            else if (identifier == face_identifier)
            {
                for (size_t i = 0; i < 3; ++i)
                {
                    std::array<size_t, 3> face = { 0, 0, 0 };
                    read_attribute(line_stream, face, 1);
                    vertex_indicies.push_back(face[0]);
                    texcoord_indices.push_back(face[1]);
                    normal_indices.push_back(face[2]);
                }
            }
            else
            {
                // unsupported identifier
            }

            line_count++;
        }

        model result;
        copy_face_elements(vertices, vertex_indicies, std::back_inserter(result.vertices));
        copy_face_elements(texcoords, texcoord_indices, std::back_inserter(result.texcoords));
        copy_face_elements(normals, normal_indices, std::back_inserter(result.normals));
        return result;
    }


    static const std::string ambient_identifier = "Ka";
    static const std::string diffuse_identifier = "Kd";
    static const std::string specular_color_identifier = "Ks";
    static const std::string specular_coefficient_identifier = "Ns";
    static const std::string disolved_identifier = "d";
    static const std::string transparency_identifier = "Tr";
    static const std::string ambient_map_identifier = "map_Ka";
    static const std::string diffuse_map_identifier = "map_Kd";
    static const std::string specular_color_map_identifier = "map_Ks";
    static const std::string alpha_map_identifier = "map_d";
    static const std::string bump_identifier = "bump";
    static const std::string bump_map_identifier = "map_bump";
    static const std::string displacement_map_identifier = "disp";

    material load_material_from_file(const std::string& path)
    {
        material result;

        std::ifstream input_stream(path);
        if (!input_stream)
        {
            std::ostringstream err;
            err << "error opening model file " << path << " for reading.";
            throw std::runtime_error(err.str());
        }

        size_t line_count = 0;
        std::string line, identifier;
        while (std::getline(input_stream, line))
        {
            std::istringstream line_stream(line);
            line_stream >> identifier;

            if (identifier == ambient_identifier)
            {
                read_attribute(line_stream, result.ambient_color);
            }
            else if (identifier == diffuse_identifier)
            {
                read_attribute(line_stream, result.diffuse_color);
            }
            else if (identifier == specular_color_identifier)
            {
                read_attribute(line_stream, result.specular_color);
            }
            else if (identifier == specular_coefficient_identifier)
            {
                read_attribute(line_stream, result.specular_coefficient);
            }
            else if (identifier == disolved_identifier || identifier == transparency_identifier)
            {
                read_attribute(line_stream, result.transparency);
            }
            else if (identifier == ambient_map_identifier)
            {
                read_attribute(line_stream, result.ambient_map_path);
            }
            else if (identifier == diffuse_map_identifier)
            {
                read_attribute(line_stream, result.diffuse_map_path);
            }
            else if (identifier == alpha_map_identifier)
            {
                read_attribute(line_stream, result.alpha_map_path);
            }
            else if (identifier == bump_identifier || identifier == bump_map_identifier)
            {
                read_attribute(line_stream, result.bump_map_path);
            }
            else if (identifier == displacement_map_identifier)
            {
                read_attribute(line_stream, result.displacement_map_path);
            }
            else
            {
                // unsupported identifier
            }
        }

        return result;
    }
}
