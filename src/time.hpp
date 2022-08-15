#pragma once
#include <cstdint>
#include <memory>

namespace QE {

struct Time {
    uint32_t fps;
    double now;
    double delta;
    void update();
    
};

extern std::unique_ptr<Time> time;

};
