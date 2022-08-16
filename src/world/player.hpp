#pragma once
#include "physics.hpp"
#include <glm/mat4x4.hpp>

namespace QE {

struct Player {
    bool jumping;
    Player();
    Physics physics;
    void update();
};

};
