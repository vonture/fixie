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

    const unsigned int texture_width = 256;
    const unsigned int texture_height = 256;

    std::vector<GLubyte> texture_data(texture_width * texture_height * 4);
    for(int y = 0; y < texture_height; ++y)
    {
        for(int x = 0; x < texture_width; ++x)
        {
            unsigned int pixel_index = (y * texture_height + x) * 4;

            texture_data[pixel_index + 0] = 0;
            texture_data[pixel_index + 1] = 0;
            texture_data[pixel_index + 2] = 0;
            texture_data[pixel_index + 3] = 0;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data.data());

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


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
        float scale = std::min<float>(width, height) * 0.75f;
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
