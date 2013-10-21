#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"

#include "GLFW/glfw3.h"

#include <algorithm>
#include <vector>

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SAMPLE_WIDTH, SAMPLE_HEIGHT, SAMPLE_NAME, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    const float vertices[] =
    {
        -0.4f, -0.4f, 0.0f, // Position
         0.0f,  0.0f,       // Texcoord
         0.4f, -0.4f, 0.0f,
         1.0f,  0.0f,
         0.4f,  0.4f, 0.0f,
         1.0f,  1.0f,
        -0.4f,  0.4f, 0.0f,
         0.0f,  1.0f,
    };
    const unsigned int buffer_size = (sizeof(vertices) / sizeof(vertices[0])) * sizeof(float);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);


    glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const size_t texture_width = 1024;
    const size_t texture_height = 1024;
    const size_t iterations = 64;

    const float seed_x = -0.4f;
    const float seed_y =  0.6f;

    std::vector<GLubyte> color_pallete(256 * 4);
    for (size_t i = 0; i < 256; i++)
    {
        size_t pixel_index = i * 4;

        color_pallete[pixel_index + 0] = GLubyte((((std::min(std::max(i, 0U), 31U)) - 0U) / 32.0f) * 255);
        color_pallete[pixel_index + 1] = GLubyte((((std::min(std::max(i, 32U), 63U)) - 32U) / 32.0f) * 255);
        color_pallete[pixel_index + 2] = GLubyte((((std::min(std::max(i, 64U), 255U)) - 192U) / 192.0f) * 255);
        color_pallete[pixel_index + 3] = 255;
    }

    std::vector<GLubyte> texture_data(texture_width * texture_height * 4);
    for(size_t y = 0; y < texture_height; ++y)
    {
        for(size_t x = 0; x < texture_width; ++x)
        {
            float homogeneous_x = ((float(x) / texture_width) - 0.5f) * 2.0f;
            float homogeneous_y = ((float(y) / texture_width) - 0.5f) * 2.0f;

            size_t i;
            for (i = 0; i < iterations; i++)
            {
                float test_x = (homogeneous_x * homogeneous_x - homogeneous_y * homogeneous_y) + seed_x;
                float test_y = (homogeneous_y * homogeneous_x + homogeneous_x * homogeneous_y) + seed_y;

                if ((test_x * test_x + test_y * test_y) > 4.0f)
                {
                    break;
                }

                homogeneous_x = test_x;
                homogeneous_y = test_y;
            }

            GLubyte result = (i != iterations) ? GLubyte((float(i) / iterations) * 255) : 0;

            size_t pallete_index = result * 4;

            size_t pixel_index = (y * texture_height + x) * 4;
            texture_data[pixel_index + 0] = color_pallete[pallete_index + 0];
            texture_data[pixel_index + 1] = color_pallete[pallete_index + 1];
            texture_data[pixel_index + 2] = color_pallete[pallete_index + 2];
            texture_data[pixel_index + 3] = color_pallete[pallete_index + 3];
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data.data());


    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / float(height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrthof(width / -2.0f, width / 2.0f, height / 2.0f, height / -2.0f, 1.0f, -1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float scale = std::min(width, height) * 0.9f;
        glScalef(scale, scale, scale);
        glRotatef(time * 50.f, 1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(float) * 5, 0);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    fixie_terminate();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
