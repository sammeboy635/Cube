
#include <stdlib.h>
#include <stdio.h>
#include "callback.h"

void callback_error(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void callback_key(GLFWwindow *screen, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(screen, GLFW_TRUE);
}