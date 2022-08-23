#include "physics.hpp"
#include <time.hpp>

using namespace QE;

Physics::Physics(Model& model) : collision(*this, model) {
}

void Physics::update() {
    transform.update();

    if (true) {
        //force *= linear_drag;
    }

    force.y -= gravity * time->delta;

    transform.position += force * glm::vec3(time->delta);

    if (transform.position.y <= 5.f) {
        transform.position.y = 5.f;
        force.y = 0;
    }
}

Physics::~Physics() {
}
