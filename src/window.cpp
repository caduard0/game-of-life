#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "aliases.hpp"
#include <algorithm>
#include <iostream>
#include "window.hpp"


Window::Window(u32 width, u32 height, std::string tittle, bool fullscreen) 
    : window(glfwCreateWindow(width, height, tittle.c_str(), nullptr, nullptr))
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    int version = gladLoadGL(glfwGetProcAddress);

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::should_close() {
    return glfwWindowShouldClose(window);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::clear(){
    glClearColor(0, 0, 0, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
