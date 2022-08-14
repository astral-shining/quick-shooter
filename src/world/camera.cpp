#include "camera.hpp"
#include <world/world.hpp>
#include <input.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace QE;

Camera::Camera() {
    transform.position.z = -1;
}

glm::mat4 Camera::getMatrix() {
    return projection * view;
}

void Camera::update() {
    // float w = window.size.x/(200+(zoom*10));
    // float h = window.size.y/(200+(zoom*10));

    // follow player
    transform = current_world->player.transform;
    yaw += input.mouseMovement.x * sensitivity;
    pitch -= input.mouseMovement.y * sensitivity;
    pitch = glm::clamp(pitch, -85.f, 85.f);
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    view = glm::lookAt(transform.position, transform.position + direction, directionUp);

    //std::printf("%f %f\n", yaw, pitch);
    // set projection
    projection = glm::perspective(glm::radians(fov), (float)window->size.x / window->size.y, 0.1f, 100.0f);
    
       //glm::ortho(-w, w, -h, h, 0.1f, 1000.0f);
}
