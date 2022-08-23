#include "collision.hpp"
#include <glm/gtx/string_cast.hpp>

using namespace QE;

Collision::Collision(Physics& physics, Model& model) : physics(physics), model(model) {
    std::printf("adding collisions\n");
    for (const Face& face : model) {
        //collision_map[v.].push_back(&physics);
    }
}

void Collision::update() {
    //collision_map[physics.transform.position]
    //std::printf("%s\n", glm::to_string(p.transform.position).data());
}
