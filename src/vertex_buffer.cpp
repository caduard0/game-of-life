#include "vertex_buffer.hpp"

#include "glad/gl.h"
#include "aliases.hpp"
#include <vector>

VertexBuffer::VertexBuffer()
    : vertex_buffer(0)
{}

void VertexBuffer::create() {
    glCreateBuffers(1, &vertex_buffer);
}

void VertexBuffer::free() {
    glDeleteBuffers(1, &vertex_buffer);
}

u32 VertexBuffer::operator&() {
    return vertex_buffer;
}

void VertexBuffer::fill(std::vector<float>& vertices) {
    glNamedBufferData(vertex_buffer, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
}
