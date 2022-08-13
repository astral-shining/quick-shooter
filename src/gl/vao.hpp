#pragma once
#include <cstdint>

namespace QE::GL {

struct VAO {
    uint32_t id;
    VAO();
    VAO(uint32_t id);

    void create();
    void destroy();
    void use();
    void unbind();
    ~VAO();
};

};