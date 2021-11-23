
#include <iostream>
#include <fstream>
#include <string>
#include "logger.h"
#include "screen.h"
#include "callback.h"
#include "../../incl/glad/gl.h"

Screen::Screen()
{
    screen_init();
}
void Screen::screen_init()
{
    int size = sizeof(float);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(callback_error);
    glfwSetKeyCallback(window, callback_key);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW); //data is null

    program = glCreateProgram();
    shader_init("src/shader/vertex_shader.txt", "src/shader/fragment_shader.txt");
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    mvpLocation = glGetUniformLocation(program, "MVP");
    vposLocation = glGetAttribLocation(program, "vPos");
    vcolLocation = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vposLocation);
    glVertexAttribPointer(vposLocation, 2, GL_FLOAT, GL_FALSE,
                          size, (void *)0);
    glEnableVertexAttribArray(vcolLocation);
    glVertexAttribPointer(vcolLocation, 3, GL_FLOAT, GL_FALSE,
                          size, (void *)(sizeof(float) * 2));
}

void Screen::shader_init(const std::string vertLocation, const std::string fragLocation)
{
    const char *vertex_shader_text = file_read_shader(vertLocation);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertexShader);

    const char *fragment_shader_text = file_read_shader(fragLocation);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragmentShader);
}
const char *Screen::file_read_shader(const std::string location)
{
    FILE *file = fopen(location.data(), "rb");

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(sizeof(char) * fileSize + 1);
    fread(buffer, sizeof(char), fileSize, file);
    fclose(file);

    buffer[fileSize] = '\0';
    //printf("%s\n", buffer); //Debuging purposing
    return buffer;
}
