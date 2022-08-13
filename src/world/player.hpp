#pragma once
#include "transform.hpp"
#include <glm/mat4x4.hpp>

namespace QE {

struct Player {
    Player();
    Transform transform;
    void update();
};

};