#pragma once
#include <cstdint>

namespace QE {

struct Time {
    uint32_t fps;
    double now;
    double delta;
    void update();
    
};

extern Time time;

};