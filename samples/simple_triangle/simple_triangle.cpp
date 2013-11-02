#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"

#include "GLFW/glfw3.h"

#include <algorithm>

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
        -0.4f, -0.4f, 0.0f,       // Position
         1.0f,  0.0f, 0.0f, 1.0f, // Color
         0.4f, -0.4f, 0.0f,
         0.0f,  1.0f, 0.0f, 1.0f,
         0.0f,  0.4f, 0.0f,
         0.0f,  0.0f, 1.0f, 1.0f
    };
    const unsigned int buffer_size = (sizeof(vertices) / sizeof(vertices[0])) * sizeof(float);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);

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
        glOrthof(width / -2.0f, width / 2.0f, height / 2.0f, height / -2.0f, 1000.0f, -1000.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float scale = std::min(static_cast<float>(width), static_cast<float>(height)) * 0.75f;
        glScalef(scale, scale, scale);
        glRotatef(time * 50.f, 1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(float) * 7, 0);

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(float) * 7, reinterpret_cast<GLvoid*>(sizeof(float) * 3));

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    fixie_terminate();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
