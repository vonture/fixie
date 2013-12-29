#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"
#include "fixie/fixie_gl_es_ext.h"

#include "GLFW/glfw3.h"

#include "sample_util/obj_loader.hpp"
#include "sample_util/tga_loader.hpp"
#include "sample_util/transformations.hpp"
#include "sample_util/vectors.hpp"
#include "sample_util/lighting.hpp"
#include "sample_util/material.hpp"
#include "sample_util/random.hpp"

#include <algorithm>
#include <functional>

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

struct light_info
{
    sample_util::light light;
    sample_util::float3 rotation_rates;
    sample_util::float3 rotation_radius;
};

void initialize_random_light(light_info& light)
{
    light.light.enabled = true;

    light.light.ambient = sample_util::construct_array(sample_util::random_between(0.0f, 0.1f),
                                                       sample_util::random_between(0.0f, 0.1f),
                                                       sample_util::random_between(0.0f, 0.1f),
                                                       1.0f);

    light.light.diffuse = sample_util::construct_array(sample_util::random_between(0.0f, 1.0f),
                                                       sample_util::random_between(0.0f, 1.0f),
                                                       sample_util::random_between(0.0f, 1.0f),
                                                       1.0f);

    light.light.specular = sample_util::construct_array(sample_util::random_between(0.0f, 1.0f),
                                                        sample_util::random_between(0.0f, 1.0f),
                                                        sample_util::random_between(0.0f, 1.0f),
                                                        1.0f);

    sample_util::x(light.rotation_rates) = sample_util::random_between(-2.0f, 2.0f);
    sample_util::y(light.rotation_rates) = sample_util::random_between(-2.0f, 2.0f);
    sample_util::z(light.rotation_rates) = sample_util::random_between(-2.0f, 2.0f);
    sample_util::x(light.rotation_radius) = sample_util::random_between(15.0f, 30.0f);
    sample_util::y(light.rotation_radius) = sample_util::random_between(15.0f, 30.0f);
    sample_util::z(light.rotation_radius) = sample_util::random_between(15.0f, 30.0f);
}

void update_light(float time, light_info& light)
{
    sample_util::x(light.light.position) = sinf(time * sample_util::x(light.rotation_rates)) * sample_util::x(light.rotation_radius);
    sample_util::y(light.light.position) = sinf(time * sample_util::y(light.rotation_rates)) * sample_util::y(light.rotation_radius);
    sample_util::z(light.light.position) = sinf(time * sample_util::z(light.rotation_rates)) * sample_util::z(light.rotation_radius);
}

void apply_light(size_t index, const light_info& light)
{
    sample_util::sync_light(GL_LIGHT0 + index, light.light);
}

void draw_light_model(const sample_util::model& light_model, const light_info& light)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float sphere_scale = 1.0f;
    glScalef(sphere_scale, sphere_scale, sphere_scale);
    glTranslatef(sample_util::x(light.light.position), sample_util::y(light.light.position), sample_util::z(light.light.position));

    glColor4f(sample_util::r(light.light.diffuse),sample_util::g(light.light.diffuse), sample_util::b(light.light.diffuse),
              sample_util::a(light.light.diffuse));

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(light_model.vertices.size()));
}

template <typename iterator_type, typename func_type>
func_type indexed_for_each(iterator_type first, iterator_type last, func_type func)
{
    for (size_t i = 0; first != last; ++first)
    {
        func(i++, *first);
    }

    return func;
}

LOAD_FIXIE_GL_FUNC(glLightfv);
LOAD_FIXIE_GL_FUNC(glLightf);
LOAD_FIXIE_GL_FUNC(glMaterialfv);
LOAD_FIXIE_GL_FUNC(glMaterialf);
LOAD_FIXIE_GL_FUNC(glEnable);
LOAD_FIXIE_GL_FUNC(glDisable);

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

    sample_util::float4 min_bound, max_bound;

    sample_util::model teapot = sample_util::load_model_from_file("teapot.obj");
    sample_util::bounds(begin(teapot.vertices), end(teapot.vertices), min_bound, max_bound);
    float teapot_radius = sample_util::distance(min_bound, max_bound) * 0.5f;
    sample_util::material teapot_material;

    GLuint teapot_position_vbo = make_model_vbo(teapot.vertices);
    GLuint teapot_normal_vbo = make_model_vbo(teapot.normals);

    GLuint teapot_vao;
    glGenVertexArraysOES(1, &teapot_vao);
    glBindVertexArrayOES(teapot_vao);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, teapot_position_vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);
    glEnableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, teapot_normal_vbo);
    glNormalPointer(GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    sample_util::model sphere = sample_util::load_model_from_file("sphere.obj");
    GLuint sphere_position_vbo = make_model_vbo(sphere.vertices);

    GLuint sphere_vao;
    glGenVertexArraysOES(1, &sphere_vao);
    glBindVertexArrayOES(sphere_vao);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, sphere_position_vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    std::vector<light_info> lights(8);
    std::for_each(begin(lights), end(lights), initialize_random_light);

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

        float cube_scale = 10.0f / teapot_radius;
        glScalef(cube_scale, cube_scale, cube_scale);
        glRotatef(time * 50.f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, sinf(time) * 25.0f);

        glBindVertexArrayOES(teapot_vao);

        sample_util::sync_material(GL_FRONT_AND_BACK, teapot_material);

        std::for_each(begin(lights), end(lights), std::bind(update_light, time, std::placeholders::_1));
        indexed_for_each(begin(lights), end(lights), apply_light);

        glEnable(GL_LIGHTING);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(teapot.vertices.size()));

        glDisable(GL_LIGHTING);
        glBindVertexArrayOES(sphere_vao);
        glMatrixMode(GL_MODELVIEW);
        std::for_each(begin(lights), end(lights), std::bind(draw_light_model, sphere, std::placeholders::_1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    fixie_terminate();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
