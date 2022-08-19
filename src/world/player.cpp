#include "player.hpp"
#include <input.hpp>
#include <cstdio>
#include <time.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "world.hpp"

using namespace QE;
Player::Player() {
    physics.transform.position.z = -5.f;
    physics.gravity = 20.f;
    world->camera.yaw = 90.f;
}

void Player::update() {
    physics.update();
    auto& position = physics.transform.position;
    auto& camera = world->camera;

    float sensivity = 0.1f;
    camera.yaw += input->mouseMovement.x * sensivity;
    camera.pitch -= input->mouseMovement.y * sensivity;

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

    if (input->getKey(Keys::SPACE) && !jumping) {
        physics.force.y = 20.f;
        jumping = true;
    }

    if (position.y == 0) {
        jumping = false;
    }


    position += direction * glm::vec3(time->delta) * 10.f;
    camera.transform.position = position;
}
