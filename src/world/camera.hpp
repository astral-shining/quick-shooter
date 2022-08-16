#pragma once
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "transform.hpp"
#include <window.hpp>

namespace QE {

struct Camera {
    Transform transform;
    float fov { 90 };
    float yaw {0};
    float pitch {0};
    glm::vec3 direction {0.0f, 0.0f, -1.0f};
    glm::vec3 directionUp {0.0f, 1.0f, 0.0f};
    glm::mat4 proj;
    glm::mat4 view;

    Camera();

    glm::mat4 getPV() const;
    
    void update();
};

};
