#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"

#include "GLFW/glfw3.h"

#include "sample_util/obj_loader.hpp"
#include "sample_util/tga_loader.hpp"
#include "sample_util/transformations.hpp"
#include "sample_util/vectors.hpp"
#include "sample_util/lighting.hpp"

#include <algorithm>

#define LOAD_FIXIE_GL_FUNC(name) \
    namespace \
    { \
        auto _##name = name; \
    }

template <size_t n>
GLuint make_model_vbo(const std::vector< std::array<GLfloat, n> >& vertices)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(GLfloat) * n * vertices.size()), vertices.data(),
                 GL_STATIC_DRAW);
    return vbo;
}

LOAD_FIXIE_GL_FUNC(glLightfv);
LOAD_FIXIE_GL_FUNC(glLightf);

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

    sample_util::model cube = sample_util::load_model_from_file("cube.obj");

    sample_util::float4 min_bound, max_bound;
    sample_util::bounds(begin(cube.vertices), end(cube.vertices), min_bound, max_bound);
    float cube_radius = sample_util::distance(min_bound, max_bound) * 0.5f;

    GLuint cube_position_vbo = make_model_vbo(cube.vertices);
    GLuint cube_normal_vbo = make_model_vbo(cube.normals);

    sample_util::model sphere = sample_util::load_model_from_file("sphere.obj");

    sample_util::bounds(begin(cube.vertices), end(cube.vertices), min_bound, max_bound);
    float sphere_radius = sample_util::distance(min_bound, max_bound) * 0.5f;

    GLuint sphere_position_vbo = make_model_vbo(sphere.vertices);

    sample_util::light light;
    light.enabled = true;
    light.diffuse = sample_util::construct_array(1.0f, 1.0f, 0.0f, 1.0f);
    sample_util::z(light.position) = -25.0f;

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
        sample_util::perspective_matrix(60.0f, ratio, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float cube_scale = 10.0f / cube_radius;
        glScalef(cube_scale, cube_scale, cube_scale);
        glRotatef(time * 50.f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, sinf(time) * 25.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, cube_position_vbo);
        glVertexPointer(4, GL_FLOAT, 0, 0);

        glEnableClientState(GL_NORMAL_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, cube_normal_vbo);
        glNormalPointer(GL_FLOAT, 0, 0);

        glDisableClientState(GL_COLOR_ARRAY);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        light.enabled = true;
        sample_util::x(light.position) = sinf(time) * 25.0f;
        sample_util::y(light.position) = cosf(time) * 25.0f;
        sample_util::sync_light(GL_LIGHT0, light);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(cube.vertices.size()));

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float sphere_scale = 2.0f / sphere_radius;
        glScalef(sphere_scale, sphere_scale, sphere_scale);
        glTranslatef(sample_util::x(light.position), sample_util::y(light.position), sample_util::z(light.position));

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, sphere_position_vbo);
        glVertexPointer(4, GL_FLOAT, 0, 0);

        glDisableClientState(GL_NORMAL_ARRAY);

        glDisableClientState(GL_COLOR_ARRAY);
        glColor4f(sample_util::r(light.diffuse), sample_util::g(light.diffuse), sample_util::b(light.diffuse), sample_util::a(light.diffuse));

        light.enabled = false;
        sample_util::sync_light(GL_LIGHT0, light);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(sphere.vertices.size()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    fixie_terminate();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
