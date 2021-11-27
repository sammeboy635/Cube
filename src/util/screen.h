#pragma once
#include "../../incl/glad/gl.h"
#include "../../incl/GLFW/glfw3.h"
#include "../../incl/linmath/linmath.h"

#include <string>

;
class Screen
{
private:
    const char *shader_file_read(const std::string location);

public:
    GLFWwindow *self;
    uint vertexBuffer, vertexShader, fragmentShader, program;
    int mvpLocation, vposLocation, vcolLocation;

    Screen();
    void screen_init();
    void shader_init(const std::string vertLocation, const std::string fragLocation);
};