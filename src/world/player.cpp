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

    float dir_x = cos(glm::radians(camera.yaw));
    float dir_z = sin(glm::radians(camera.yaw));

    glm::vec3 direction {};
    if (input->getKey(Keys::W)) {
        direction += glm::vec3(dir_x, 0.0f, dir_z);
    }

    if (input->getKey(Keys::S)) {
        direction += glm::vec3(-dir_x, 0.0f, -dir_z);
    }

    if (input->getKey(Keys::A)) {
        direction += glm::vec3(dir_z, 0.0f, -dir_x);
    }

    if (input->getKey(Keys::D)) {
        direction += glm::vec3(-dir_z, 0.0f, dir_x);
    }
    transform.position += direction * glm::vec3(time->delta);
}
