#pragma once


#include <vector>

#include "aliases.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"


class VertexArray {
public:
    virtual ~VertexArray() {};
    
    virtual void create() = 0;
    virtual void free() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void render() = 0;

    u32 vertex_array;
private:
};

class SimpleVertexArray : public VertexArray {
public:
    SimpleVertexArray();
    ~SimpleVertexArray();

    void create() override;
    void free() override;
    void bind() override;
    void unbind() override;
    void render() override;
    void fill_data(std::vector<float>& vertices, std::vector<u32>& indices);

private:
    VertexBuffer vertex_buffer;
    IndexBuffer index_buffer;
    u32 index_size;

    bool have_data;
    bool already_exist;
};

class BlockVertexArray : public VertexArray {
public:
    BlockVertexArray();
    ~BlockVertexArray();

    void create() override;
    void free() override;
    void bind() override;
    void unbind() override;
    void render() override;
    void fill_data(std::vector<float>& vertices, std::vector<u32>& indices);

private:
    VertexBuffer vertex_buffer;
    IndexBuffer index_buffer;
    u32 index_size;

    bool have_data;
    bool already_exist;
};
