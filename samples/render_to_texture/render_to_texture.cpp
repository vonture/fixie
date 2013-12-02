#include "fixie/fixie.h"
#include "fixie/fixie_gl_es.h"
#include "fixie/fixie_gl_es_ext.h"

#include "GLFW/glfw3.h"

#include "sample_util/obj_loader.hpp"
#include "sample_util/transformations.hpp"
#include "sample_util/random.hpp"

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

    std::string extension = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
    if (extension.find("GL_OES_framebuffer_object") == std::string::npos ||
        extension.find("GL_OES_depth24") == std::string::npos)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    sample_util::model m = sample_util::load_model_from_file("cube.obj");

    GLuint position_vbo = make_model_vbo(m.vertices);
    GLuint texcoord_vbo = make_model_vbo(m.texcoords);

    const size_t framebuffer_count = 2;

    GLuint framebuffer_textures[framebuffer_count];
    glGenTextures(framebuffer_count, framebuffer_textures);

    GLuint framebuffer_depth_renderbuffers[framebuffer_count];
    glGenRenderbuffersOES(framebuffer_count, framebuffer_depth_renderbuffers);

    GLuint framebuffers[framebuffer_count];
    glGenFramebuffersOES(framebuffer_count, framebuffers);

    GLsizei framebuffer_width = SAMPLE_WIDTH;
    GLsizei framebuffer_height = SAMPLE_WIDTH;
    for (size_t i = 0; i < framebuffer_count; i++)
    {
        glBindTexture(GL_TEXTURE_2D, framebuffer_textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, framebuffer_width, framebuffer_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glBindRenderbufferOES(GL_RENDERBUFFER_OES, framebuffer_depth_renderbuffers[i]);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT24_OES, framebuffer_width, framebuffer_height);

        glBindFramebufferOES(GL_FRAMEBUFFER_OES, framebuffers[i]);
        glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_TEXTURE_2D, framebuffer_textures[i], 0);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, framebuffer_depth_renderbuffers[i]);
    }

    const size_t iterations = 10;
    std::array<std::array<float, 3>, iterations> cube_rotate_directions;
    std::array<std::array<float, 3>, iterations> cube_colors;
    for (size_t i = 0; i < iterations; i++)
    {
        for (size_t j = 0; j < cube_rotate_directions[i].size(); j++)
        {
            cube_rotate_directions[i][j] = sample_util::random_between(-50.0f, 50.0f);
        }
        for (size_t j = 0; j < cube_colors[i].size(); j++)
        {
            cube_colors[i][j] = sample_util::random_between(0.0f, 1.0f);
        }
    }

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / float(height);

        if (width != framebuffer_width || height != framebuffer_height)
        {
            framebuffer_width = width;
            framebuffer_height = height;
            for (size_t i = 0; i < framebuffer_count; i++)
            {
                glBindTexture(GL_TEXTURE_2D, framebuffer_textures[i]);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, framebuffer_width, framebuffer_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

                glBindRenderbufferOES(GL_RENDERBUFFER_OES, framebuffer_depth_renderbuffers[i]);
                glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT24_OES, framebuffer_width, framebuffer_height);
            }
        }

        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -50.0f);
        sample_util::perspective_matrix(60.0f, ratio, 0.1f, 100.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
        glVertexPointer(4, GL_FLOAT, 0, 0);


        for (size_t i = 0; i < iterations; i++)
        {
            if (i + 1 < iterations)
            {
                glBindFramebufferOES(GL_FRAMEBUFFER_OES, framebuffers[1 - (i % 2)]);
                glClearColor(cube_colors[i + 1][0], cube_colors[i + 1][1], cube_colors[i + 1][2], 1.0f);
            }
            else
            {
                glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            }

            if (i > 0)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, framebuffer_textures[i % 2]);

                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
                glTexCoordPointer(3, GL_FLOAT, 0, 0);

                glDisableClientState(GL_COLOR_ARRAY);
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            }
            else
            {
                glDisable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);

                glDisableClientState(GL_TEXTURE_COORD_ARRAY);

                glDisableClientState(GL_COLOR_ARRAY);
                glColor4f(cube_colors[0][0], cube_colors[0][1], cube_colors[0][2], 1.0f);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            float scale = 15.0f;
            glScalef(scale, scale, scale);
            glRotatef(time * cube_rotate_directions[i][0], 1.0f, 0.0f, 0.0f);
            glRotatef(time * cube_rotate_directions[i][1], 0.0f, 1.0f, 0.0f);
            glRotatef(time * cube_rotate_directions[i][2], 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, 0.0f, 25.0f);

            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m.vertices.size()));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(framebuffer_count, framebuffer_textures);
    glDeleteRenderbuffersOES(framebuffer_count, framebuffer_depth_renderbuffers);
    glDeleteFramebuffersOES(framebuffer_count, framebuffers);

    glDeleteBuffers(1, &position_vbo);
    glDeleteBuffers(1, &texcoord_vbo);

    fixie_terminate();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
