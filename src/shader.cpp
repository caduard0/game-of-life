#include "shader.hpp"

#include <glad/gl.h>

Shader::Shader() {
    program = glCreateProgram();
    shaders[0] = glCreateShader(GL_VERTEX_SHADER);
    shaders[1] = glCreateShader(GL_FRAGMENT_SHADER);

    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);
}

Shader::~Shader() {
    for (const auto &shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    glDeleteProgram(program);
}

bool Shader::loadShader(const char* source_code, Type type) {

    glShaderSource(shaders[type], 1, &source_code, nullptr);
    glCompileShader(shaders[type]);

    GLint is_compiled;
    glGetShaderiv(shaders[type], GL_COMPILE_STATUS, &is_compiled);

    return is_compiled == GL_TRUE;
}

void Shader::setUniformMat4(const char* name, const float* data) {
    this->bind();

    int location = glGetUniformLocation(program, name);

    glUniformMatrix4fv(location, 1, GL_TRUE, data);
}

void Shader::setUniformVec3(const char* name, const float* data) {
    this->bind();

    int location = glGetUniformLocation(program, name);

    glUniform3fv(location, 1, data);
}

void Shader::bind() {
    glUseProgram(program);
}

bool Shader::link() {
    glLinkProgram(program);

    GLint is_linked;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);

    return is_linked == GL_TRUE;
}
