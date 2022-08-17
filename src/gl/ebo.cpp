#include <gl/ebo.hpp>
#include <GLES3/gl3.h>
#include <cstdio>

using namespace QE::GL;

EBO::EBO(std::initializer_list<uint32_t> i) {
    create();
    use();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(decltype(i)::value_type), i.begin(), GL_STATIC_DRAW);
}

void EBO::create() {
    glGenBuffers(1, &id);
    std::printf("created ebo: %d\n", id);
}

EBO::~EBO() {
    glDeleteBuffers(1, &id);
    std::printf("destroyed ebo: %d\n", id);
}

void EBO::use() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
}



