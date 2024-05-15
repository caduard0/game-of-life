#pragma once

#include "aliases.hpp"

class Shader {
public:
    enum Type {
        VertexShader,
        FragmentShader
    };

    u32 program;
    u32 shaders[2];

    Shader();
    ~Shader();

    bool loadShader(const char* source_code, Type type);

    void setUniformMat4(const char* name, const float* data);
    void setUniformVec3(const char* name, const float* data);

    void bind();
    bool link();

};
