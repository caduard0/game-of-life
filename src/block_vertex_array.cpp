#include "vertex_array.hpp"

#include "glad/gl.h"
#include "aliases.hpp"
#include <vector>

BlockVertexArray::BlockVertexArray()
    : vertex_buffer(VertexBuffer()), index_buffer(IndexBuffer()), index_size(0), have_data(false), already_exist(false)
{}

BlockVertexArray::~BlockVertexArray() {
    free();
}

void BlockVertexArray::create() {
    if (already_exist) free();
    glCreateVertexArrays(1, &vertex_array);
    glEnableVertexArrayAttrib(vertex_array, 0);
    glVertexArrayAttribFormat(vertex_array, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vertex_array, 0, 0);

    glEnableVertexArrayAttrib(vertex_array, 1);
    glVertexArrayAttribFormat(vertex_array, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float));
    glVertexArrayAttribBinding(vertex_array, 1, 0);

    vertex_buffer.create();
    index_buffer.create();
    already_exist = true;
}

void BlockVertexArray::free() {
    if (!already_exist) return;
    glDeleteVertexArrays(1, &vertex_array);
    vertex_buffer.free();
    index_buffer.free();

    index_size = 0;
    have_data = false;
    already_exist = false;
}

void BlockVertexArray::bind() {
    glBindVertexArray(vertex_array);
}

void BlockVertexArray::unbind() {
    glBindVertexArray(0);
}

void BlockVertexArray::render() {
    if (!have_data) return;
    glDrawElements(GL_TRIANGLES, index_size, GL_UNSIGNED_INT, nullptr);
}

void BlockVertexArray::fill_data(std::vector<float>& vertices, std::vector<u32>& indices) {
    vertex_buffer.fill(vertices);
    index_buffer.fill(indices);
    index_size = indices.size();

    glVertexArrayElementBuffer(vertex_array, &index_buffer);
    glVertexArrayVertexBuffer(vertex_array, 0, &vertex_buffer, 0, 6 * sizeof(float));

    have_data = true;
}
