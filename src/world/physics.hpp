#pragma once
#include "transform.hpp"

namespace QE {

struct Physics {
    Transform transform;
    glm::vec3 force;
    float gravity {0};

    void update();
};

};
