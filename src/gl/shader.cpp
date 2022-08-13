#include "shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <GLES3/gl3.h>
#include <cstdio>
#include <util/die.hpp>
#include <world/world.hpp>

using namespace QE::GL;

Shader* QE::GL::current_shader;

Shader::Shader(const char* vSource_, const char* fSource_) : vSource(vSource_), fSource(fSource_) {
    list.push_back(this);
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glShaderSource(vs, 1, &vSource, NULL);
    glShaderSource(fs, 1, &fSource, NULL);
    glCompileShader(vs);
    glCompileShader(fs);

    // Check errors
    int success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        die("ERROR: Compiling vertex shader %s", infoLog);
    }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        die("ERROR: Compiling fragment shader %s", infoLog);
    }

    // Link shaders
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    auto setsize = [] (GLenum type, uint32_t& size) {
        switch (type) {
        case GL_FLOAT_VEC3:
            size = 3;
            break;
        case GL_FLOAT_MAT4:
            size = 4;
            break;
        case GL_FLOAT_VEC2:
            size = 2;
            break;
        case GL_SAMPLER_2D:
        case GL_FLOAT:
            size = 1;
            break;
        default:
            die("ERROR: undefined shader type %d", type);
            //std::cerr << "udentified shader type: " << type << std::endl;
            break;
        }
    };

    GLint count;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
    for (int i {}; i < count; i++) {
        char name[16];
        GLenum type;
        int size;
        glGetActiveAttrib(program, (GLuint)i, sizeof(name), NULL, &size, &type, name);
        attribs[name].location = glGetAttribLocation(program, name);
        attribs[name].index = i;
        setsize(type, attribs[name].size);
        attribs[name].size *= size;
    }

    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    for (int i{}; i < count; i++) {
        char name[16];
        GLenum type;
        glGetActiveUniform(program, (GLuint) i, sizeof(name), NULL, NULL, &type, name);
        uniforms[name].location = glGetUniformLocation(program, name);
        uniforms[name].index = i;
        uniforms[name].type = type;
        setsize(type, uniforms[name].size);
    }
}

void Shader::use() {
    glUseProgram(program);
    current_world->updateUniforms(*this);
    current_shader = this;
}

void Shader::setAttribute(std::initializer_list<const char*> arr, VBO& vbo) {
    uint32_t size_row {};
    for (auto name : arr) {
        size_row += attribs[name].size;
    }

    uint32_t c {};
    for (auto name : arr) {
        uint32_t size = attribs[name].size;
        AttribInfo& info = attribs[name];
        glVertexAttribPointer(
            info.index,
            size,
            vbo.type,
            GL_FALSE,
            size_row * vbo.type_size,
            (void*)(c * vbo.type_size)
        );
        glEnableVertexAttribArray(info.index);
        c += size;
    }
}

void Shader::uniform(const char* name, const glm::mat4& v) {
    glUniformMatrix4fv(uniforms[name].location, 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::uniform(const char* name, const int v) {
    glUniform1i(uniforms[name].location, v);
}

void Shader::uniform(const char* name, const glm::vec2& v) {
    glUniform2fv(uniforms[name].location, 1, glm::value_ptr(v));
}

void Shader::uniform(const char* name, const float v) {
    glUniform1f(uniforms[name].location, v);
}

void Shader::uniform(const char* name, const glm::uvec2& v) {
    glUniform2uiv(uniforms[name].location, 1, glm::value_ptr(v));
}

void Shader::uniform(const char* name, const glm::vec3& v) {
    glUniform3fv(uniforms[name].location, 1, glm::value_ptr(v));
}

uint32_t Shader::getProgram() const {
    return program;
}

uint32_t Shader::getAttrib(const char* name) const {
    return glGetAttribLocation(program, name);
}

const Shader::AttribInfo& Shader::getAttribInfo(const char* name) const {
    return attribs.at(name);
}

void Shader::destroy() {
    glDeleteProgram(program);
}

Shader::~Shader() {
    if (compiled) {
        destroy();
    }
}

