#include "world.hpp"

#include <gl/shader.hpp>
#include "triangle.hpp"

#include <time.hpp>

using namespace QE;

World::World() {
    current_world = this;
}

void World::update() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    static Triangle triangle;
    camera.update();
    player.update();
    triangle.render();
}

void World::updateUniforms(GL::Shader& s) {
    s.uniform("u_time", (float) time.now);
    s.uniform("u_res", (glm::vec2) window.size);
}
