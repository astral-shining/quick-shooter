#pragma once
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "transform.hpp"
#include <window.hpp>

namespace QE {

struct Camera {
    Transform transform;
    float fov;
    float yaw;
    float pitch;
    glm::vec3 directionUp;

    glm::vec3 direction;
    glm::mat4 proj;
    glm::mat4 view;

    Camera();

    glm::mat4 getPV() const;
    
    void update();
};

};
