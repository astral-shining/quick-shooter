#include "physics.hpp"
#include <time.hpp>

using namespace QE;

void Physics::update() {
    transform.update();
    transform.position += force;
    force.y -= gravity * time->delta;

    if (transform.position.y <= 0) {
        transform.position.y = 0;
        force.y = 0;
    }
}
