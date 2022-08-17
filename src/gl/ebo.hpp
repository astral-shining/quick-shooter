#pragma once
#include <cstdint>
#include <initializer_list>

namespace QE::GL {

struct EBO {
    uint32_t id {};
    EBO(std::initializer_list<uint32_t> e);
    EBO(EBO&& other);
    EBO& operator=(EBO&& other);

    EBO(const EBO& other) = delete;
    EBO& operator=(const EBO& other) = delete;

    void create();
    void destroy();
    void use();
    void unbind();
    ~EBO();

    void bufferData();
};

};
