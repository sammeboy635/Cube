#pragma once
#include "../../incl/GLFW/glfw3.h"
#include "../../incl/linmath/linmath.h"
#include "../../incl/glad/gl.h"

#include <string>

;
class Screen
{
private:
    const char *file_read_shader(const std::string location);

public:
    GLFWwindow *window;
    uint vertexBuffer, vertexShader, fragmentShader, program;
    int mvpLocation, vposLocation, vcolLocation;

    Screen();
    void Screen::screen_init();
    void shader_init(const std::string vertLocation, const std::string fragLocation);
};