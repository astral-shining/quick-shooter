#pragma once
#include "transform.hpp"
#include <list>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "collision.hpp"

namespace QE {

struct Collision;

struct Physics {
    Collision collision;
    Transform transform;
    glm::vec3 force;
    float linear_drag {0.9f};

    float gravity {0};

    Physics(Model& model);
    ~Physics();
    void update();
};

};
