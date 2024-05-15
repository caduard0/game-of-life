#pragma once

#include "aliases.hpp"
#include <vector>

class VertexBuffer {
private:
    u32 vertex_buffer;
public:
    VertexBuffer();
    void create();
    void free();

    u32 operator&();

    void fill(std::vector<float>& vertices);
};
