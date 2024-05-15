#pragma once

#include "aliases.hpp"
#include <vector>

class IndexBuffer {
private:
    u32 index_buffer;
public:
    IndexBuffer();
    void create();
    void free();
    
    u32 operator&();

    void fill(std::vector<u32>& indices);
};
