#include "world.hpp"

#include <gl/shader.hpp>
#include "triangle.hpp"

#include <time.hpp>

using namespace QE;

World::World() {
    //current_world = this;
}

void World::update() {
    camera.update();
    player.update();
    triangle.update();
}

void World::updateUniforms(GL::Shader& s) {
    s.uniform("u_time", (float) time->now);
    s.uniform("u_res", (glm::vec2) window->size);
    s.uniform("u_view", camera.view);
    s.uniform("u_proj", camera.proj);
}

std::unique_ptr<World> QE::world;
