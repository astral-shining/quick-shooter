#pragma once
#include "transform.hpp"


namespace QE {

struct Light {
    Light();
    Transform transform;
    float intensity;
};

};
