#include "physics.hpp"
#include <time.hpp>

using namespace QE;

void Physics::update() {
    transform.update();
    transform.position += force * glm::vec3(time->delta);
    force.y -= gravity * time->delta;

    if (transform.position.y <= 5.f) {
        transform.position.y = 5.f;
        force.y = 0;
    }
}
