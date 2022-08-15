#include "player.hpp"
#include <input.hpp>
#include <cstdio>
#include <time.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "world.hpp"

using namespace QE;
Player::Player() {
    transform.position.z = -1.f;
}

void Player::update() {
    auto& camera = world->camera;

    float sensivity = 0.1f;
    camera.yaw += input->mouseMovement.x * sensivity;
    camera.pitch -= input->mouseMovement.y * sensivity;
    camera.transform.position = transform.position;

    glm::vec3 direction {};
    glm::vec3 camera_direction = world->camera.direction;
    //glm::vec3 direction = current_world->camera.direction * glm::vec3(time.delta);
    if (input->getKey(Keys::W)) {
        direction += glm::vec3(camera_direction.x, 0.0f, camera_direction.z);
    }

    if (input->getKey(Keys::S)) {
        direction += glm::vec3(-camera_direction.x, 0.0f, -camera_direction.z);
    }

    if (input->getKey(Keys::A)) {
        direction += glm::vec3(camera_direction.z, 0.0f, -camera_direction.x);
    }

    if (input->getKey(Keys::D)) {
        direction += glm::vec3(-camera_direction.z, 0.0f, camera_direction.x);
    }
    std::printf("%s\n", glm::to_string(direction).data());    
    transform.position += direction * glm::vec3(time->delta);
}
