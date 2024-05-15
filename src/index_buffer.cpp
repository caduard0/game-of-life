#include "index_buffer.hpp"

#include "glad/gl.h"
#include "aliases.hpp"
#include <vector>

IndexBuffer::IndexBuffer()
    : index_buffer(0)
{}

void IndexBuffer::create() {
    glCreateBuffers(1, &index_buffer);
}

void IndexBuffer::free() {
    glDeleteBuffers(1, &index_buffer);
}

u32 IndexBuffer::operator&() {
    return index_buffer;
}

void IndexBuffer::fill(std::vector<u32>& indices) {
    glNamedBufferData(index_buffer, indices.size() * sizeof(u32), &indices[0], GL_DYNAMIC_DRAW);
}
