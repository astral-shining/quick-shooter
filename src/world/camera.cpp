#include "camera.hpp"
#include <world/world.hpp>
#include <input.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace QE;

Camera::Camera() : 
    fov(90), 
    yaw(90),
    pitch(),
    directionUp(0.0f, 1.0f, 0.0f) {
//    transform.position.z = -1;
}

glm::mat4 Camera::getPV() const {
    return proj * view;
}

void Camera::update() {
    // float w = window.size.x/(200+(zoom*10));
    // float h = window.size.y/(200+(zoom*10));
    pitch = glm::clamp(pitch, -89.f, 89.f);
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    view = glm::lookAt(transform.position, transform.position + direction, directionUp);

    //std::printf("%f %f\n", yaw, pitch);
    // set projection
    proj = glm::perspective(glm::radians(fov), (float)window->size.x / window->size.y, 0.001f, 100.0f);
    
}
