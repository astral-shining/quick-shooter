#pragma once
#include <initializer_list>
#include <cstdint>

struct Model {
    std::initializer_list<float> data;
    uint32_t count;
};
