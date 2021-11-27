
#include <iostream>
#include <fstream>
#include <string>
#include "screen.h"
#include "logger.h"
#include "callback.h"
#include <GLFW/glfw3.h>

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

    self = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!self)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(callback_error);
    glfwSetKeyCallback(self, callback_key);

    glfwMakeContextCurrent(self);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //data is null

    program = glCreateProgram();
    shader_init("src/shader/vertex_shader.txt", "src/shader/fragment_shader.txt");
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    mvpLocation = glGetUniformLocation(program, "MVP");
    vposLocation = glGetAttribLocation(program, "vPos");
    vcolLocation = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vposLocation);
    glVertexAttribPointer(vposLocation, 2, GL_FLOAT, GL_FALSE, size, (void *)0);
    glEnableVertexAttribArray(vcolLocation);
    glVertexAttribPointer(vcolLocation, 3, GL_FLOAT, GL_FALSE, size, (void *)(sizeof(float) * 2));
}

void Screen::shader_init(const std::string vertLocation, const std::string fragLocation)
{
    const char *vertex_shader_text = shader_file_read(vertLocation);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertexShader);

    const char *fragment_shader_text = shader_file_read(fragLocation);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragmentShader);
}
const char *Screen::shader_file_read(const std::string location)
{
    FILE *file = fopen(location.data(), "rb");
    if (file == NULL)
        error_log("File ERROR:");

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
