
#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include "../incl/linmath/linmath.h"
#include "./util/screen.h"

#include <stdlib.h>
#include <stdio.h>
#include <fstream>

static const struct
{
    float x, y;
    float r, g, b;
} vertices[] =
    {
        {-0.5f, 0.5f, 1.f, 0.f, 0.f},
        {-0.5f, -0.5f, 0.f, 1.f, 0.f},
        {0.5f, 0.5f, 0.f, 0.f, 1.f},
        {0.5f, -0.5f, 0.f, 0.f, 1.f}};

int main(void)
{
    Screen window;
    while (!glfwWindowShouldClose(window.self))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window.self, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //mat4x4_identity(m);
        //mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //mat4x4_mul(mvp, p, m);

        glUseProgram(window.program);
        glUniformMatrix4fv(window.mvpLocation, 1, GL_FALSE, (const GLfloat *)mvp);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glMultiDrawArrays(GL_TRIANGLE_STRIP, vertices, 4)

            glfwSwapBuffers(window.self);
        glfwPollEvents();
    }

    glfwDestroyWindow(window.self);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
