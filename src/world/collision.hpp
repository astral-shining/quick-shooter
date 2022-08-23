#pragma once
#include <models/model.hpp>
#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>
#include <string>
#include <glm/gtx/hash.hpp>

namespace QE {

struct Physics;

struct Collision {
    Physics& physics;
    Model& model;
    inline static std::unordered_map<glm::ivec3, std::vector<Physics*>> collision_map;
    bool is_colliding {};
    Collision(Physics& physics, Model& model);
    void update();
};

};

#include "physics.hpp"
