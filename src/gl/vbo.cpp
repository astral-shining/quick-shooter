#include "vbo.hpp"
#include <cstdio>
#include <GLES3/gl3.h>

using namespace QE::GL;

VBO::VBO() {
    create();
}

VBO::VBO(std::initializer_list<float> f, uint32_t draw_type) {
    create();
    type = GL_FLOAT;
    type_size = 4;
    size = f.size();
    buffer = (void*)f.begin();
    bufferData(draw_type);
}

VBO::VBO(std::initializer_list<std::array<glm::vec3, 3>> f, uint32_t draw_type) {
    create();
    type = GL_FLOAT;
    type_size = 4;
    size = f.size()*9;
    buffer = (void*)f.begin();
    bufferData(draw_type);
}

VBO::VBO(uint32_t otherid) : id(otherid) {
}

VBO::VBO(VBO&& other) : id(other.id) {
    other.id = 0;
}

VBO& VBO::operator=(VBO&& other) {
    destroy();
    id = other.id;
    other.id = 0;
    return *this;
}

void VBO::create() {
    glGenBuffers(1, &id);
    std::printf("created vbo: %d\n", id);
}

void VBO::destroy() {
    glDeleteBuffers(1, &id);
    std::printf("destroyed vbo: %d\n", id);
    id = 0;
}

VBO::~VBO() {
    destroy();
}

void VBO::use() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

void VBO::bufferData(uint32_t draw_type) {
    use();
    glBufferData(GL_ARRAY_BUFFER, size * type_size, buffer, draw_type);
}
