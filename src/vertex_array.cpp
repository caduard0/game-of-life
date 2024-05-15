#include "vertex_array.hpp"

#include "glad/gl.h"
#include "aliases.hpp"
#include <vector>

SimpleVertexArray::SimpleVertexArray()
    : vertex_buffer(VertexBuffer()), index_buffer(IndexBuffer()), index_size(0), have_data(false), already_exist(false)
{}

SimpleVertexArray::~SimpleVertexArray() {
    free();
}

void SimpleVertexArray::create() {
    if (already_exist) free();
    glCreateVertexArrays(1, &vertex_array);
    glEnableVertexArrayAttrib(vertex_array, 0);
    glVertexArrayAttribFormat(vertex_array, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vertex_array, 0, 0);

    vertex_buffer.create();
    index_buffer.create();
    already_exist = true;
}

void SimpleVertexArray::free() {
    if (!already_exist) return;
    glDeleteVertexArrays(1, &vertex_array);
    vertex_buffer.free();
    index_buffer.free();

    index_size = 0;
    have_data = false;
    already_exist = false;
}

void SimpleVertexArray::bind() {
    glBindVertexArray(vertex_array);
}

void SimpleVertexArray::unbind() {
    glBindVertexArray(0);
}

void SimpleVertexArray::render() {
    if (!have_data) return;
    glDrawElements(GL_TRIANGLES, index_size, GL_UNSIGNED_INT, nullptr);
}

void SimpleVertexArray::fill_data(std::vector<float>& vertices, std::vector<u32>& indices) {
    vertex_buffer.fill(vertices);
    index_buffer.fill(indices);
    index_size = indices.size();

    glVertexArrayElementBuffer(vertex_array, &index_buffer);
    glVertexArrayVertexBuffer(vertex_array, 0, &vertex_buffer, 0, 3 * sizeof(float));

    have_data = true;
}
