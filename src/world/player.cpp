#include "player.hpp"
#include <input.hpp>
#include <cstdio>
#include <time.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <models/player.hpp>
#include <emscripten/html5.h>
#include "world.hpp"

using namespace QE;
Player::Player() : physics(player_collision_model) {
    physics.transform.position.z = -5.f;
    physics.gravity = 100.f;
    world->camera.yaw = 90.f;
}

void Player::update() {
    physics.update();
    auto& position = physics.transform.position;
    auto& force = physics.force;
    auto& camera = world->camera;

    float sensivity = 0.3f;
    camera.yaw += input->mouseMovement.x * sensivity;
    camera.pitch -= input->mouseMovement.y * sensivity;

    float dir_x = cos(glm::radians(camera.yaw));
    float dir_z = sin(glm::radians(camera.yaw));

    glm::vec3 direction {};
    if (input->getKey(Keys::W)) {
        force += glm::vec3(dir_x, 0.0f, dir_z);
    }

    if (input->getKey(Keys::S)) {
        force += glm::vec3(-dir_x, 0.0f, -dir_z);
    }

    if (input->getKey(Keys::A)) {
        force += glm::vec3(dir_z, 0.0f, -dir_x);
        //direction += glm::vec3(dir_z, 0.0f, -dir_x);
    }

    if (input->getKey(Keys::D)) {
        force += glm::vec3(-dir_z, 0.0f, dir_x);
        //direction += glm::vec3(-dir_z, 0.0f, dir_x);
    }

    if (input->getKey(Keys::SPACE) && !jumping) {
        physics.force.y = 50.f;
        jumping = true;
    }

    if (position.y == 5.f) {
        jumping = false;
    }

    position += direction * glm::vec3(time->delta) * 30.f;
    camera.transform.position = position;

    glm::vec3 p = camera.transform.position-world->box.physics.transform.position+camera.direction*glm::distance(camera.transform.position, world->box.physics.transform.position);
    //std::printf("%s\n", glm::to_string(p).data());
    float size = 1.f;
    if (glm::all(glm::lessThan(p, glm::vec3(world->box.physics.transform.scale.x))) && glm::all(glm::greaterThan(p, glm::vec3(-world->box.physics.transform.scale.y)))) {
        world->box.color = {1.f, 1.f, 1.f};
    } else {
        world->box.color = {0.f, 1.f, 1.f};
    }
}
