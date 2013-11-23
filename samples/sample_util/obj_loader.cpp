#include "obj_loader.hpp"

#include <fstream>
#include <sstream>
#include <map>
#include <functional>

namespace sample_util
{
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

    model_material load_material_from_file(const std::string& path)
    {
        model_material result;

        std::ifstream input_stream(path);
        if (!input_stream)
        {
            std::ostringstream err;
            err << "error opening model file " << path << " for reading.";
            throw std::runtime_error(err.str());
        }

        using namespace std::placeholders;
        std::map< std::string, std::function<void (std::istringstream&)> > read_function_map;
        read_function_map["Ka"] = std::bind(read_attribute<float, 3>, _1, result.ambient_color, 0);
        read_function_map["Kd"] = std::bind(read_attribute<float, 3>, _1, result.diffuse_color, 0);
        read_function_map["Ks"] = std::bind(read_attribute<float, 3>, _1, result.specular_color, 0);
        read_function_map["Ns"] = std::bind(read_attribute<float>, _1, result.specular_coefficient);
        read_function_map["d"] = std::bind(read_attribute<float>, _1, result.transparency);
        read_function_map["Tr"] = std::bind(read_attribute<float>, _1, result.transparency);
        read_function_map["map_Ka"] = std::bind(read_attribute<std::string>, _1, result.ambient_map_path);
        read_function_map["map_Kd"] = std::bind(read_attribute<std::string>, _1, result.diffuse_map_path);
        read_function_map["map_Ks"] = std::bind(read_attribute<std::string>, _1, result.specular_color_map_path);
        read_function_map["map_d"] = std::bind(read_attribute<std::string>, _1, result.alpha_map_path);
        read_function_map["bump"] = std::bind(read_attribute<std::string>, _1, result.bump_map_path);
        read_function_map["map_bump"] = std::bind(read_attribute<std::string>, _1, result.bump_map_path);
        read_function_map["disp"] = std::bind(read_attribute<std::string>, _1, result.displacement_map_path);

        std::string line;
        while (std::getline(input_stream, line))
        {
            std::istringstream line_stream(line);
            std::string identifier;
            line_stream >> identifier;

            auto read_func = read_function_map.find(identifier);
            if (read_func != end(read_function_map))
            {
                read_func->second(line_stream);
            }
        }

        return result;
    }
}
