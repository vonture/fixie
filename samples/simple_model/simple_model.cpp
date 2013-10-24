#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"

#include "GLFW/glfw3.h"

#include "sample_util/obj_loader.hpp"
#include "sample_util/tga_loader.hpp"
#include "sample_util/transformations.hpp"

#include <algorithm>

template <size_t n>
GLuint make_model_vbo(const std::vector< std::array<GLfloat, n> >& vertices)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * n * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    return vbo;
}

GLuint make_tga_texture(const tga_image& img)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data.data());
    return texture;
}

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

    model m = load_model_from_file("suzanne.obj");
    tga_image image = load_tga_image_from_file("gradient.tga");

    GLuint position_vbo = make_model_vbo(m.vertices);
    GLuint normal_vbo = make_model_vbo(m.normals);
    GLuint texcoord_vbo = make_model_vbo(m.texcoords);

    GLuint texture = make_tga_texture(image);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / float(height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -50.0f);
        perspective_matrix(60.0f, ratio, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float scale = 10.0f;
        glScalef(scale, scale, scale);
        glRotatef(time * 50.f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, sinf(time) * 25.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
        glVertexPointer(4, GL_FLOAT, 0, 0);

        glEnableClientState(GL_NORMAL_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
        glNormalPointer(GL_FLOAT, 0, 0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
        glTexCoordPointer(3, GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, m.vertices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    fixie_terminate();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
