#include "world.hpp"

#include <gl/shader.hpp>

#include <models/map.hpp>
#include <time.hpp>
#include <input.hpp>

using namespace QE;

World::World() : map(map_model) {
}

void World::update() {
    camera.update();
    map.update();
    player.update();
}

void World::updateUniforms(GL::Shader& s) {
    s.uniform("u_time", (float) time->now);
    s.uniform("u_res", (glm::vec2) window->size);
    s.uniform("u_view", camera.view);
    s.uniform("u_view_pos", camera.transform.position);
    s.uniform("u_proj", camera.proj);
    s.uniform("u_light", light.transform.position);
    s.uniform("u_light_intensity", light.intensity);
}

std::unique_ptr<World> QE::world;
