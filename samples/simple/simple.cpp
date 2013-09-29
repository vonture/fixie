#include "fixie.h"
#include "fixie_gl_es.h"

#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "fixie testbed", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    fixie_context fixie_ctx = fixie_create_context();

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
        glOrthof(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(time * 50.f, 0.0f, 0.0f, 1.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(float) * 7, 0);

        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(float) * 7, (GLvoid*)(sizeof(float) * 3));

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    fixie_destroy_context(fixie_ctx);
    return 0;
}
