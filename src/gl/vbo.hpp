#pragma once
#include <cstdint>
#include <initializer_list>
#include <glm/vec3.hpp>
#include <array>

namespace QE::GL {

struct VBO {
    uint32_t id {};
    uint32_t type;
    uint32_t type_size;
    uint32_t size;
    void* buffer;
    
    VBO();
    VBO(std::initializer_list<float> f, uint32_t draw_type = 0x88E4);
    VBO(std::initializer_list<std::array<glm::vec3, 3>> f, uint32_t draw_type = 0x88E4);

    VBO(uint32_t vbo);
    VBO(VBO&& other);
    VBO& operator=(VBO&& other);
    
    VBO(const VBO &other) = delete;
	VBO& operator=(const VBO &other) = delete;

    void create();
    void destroy();
    void use();
    void unbind();
    ~VBO();

    void bufferData(uint32_t draw_type = 0x88E4);
};

};