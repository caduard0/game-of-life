#pragma once

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "aliases.hpp"
#include <string>

class Window {
    GLFWwindow* window;

public:
    Window(u32 width, u32 height, std::string tittle, bool fullscreen);
    ~Window();

    bool should_close();
    
    void update();

    void clear();
};
