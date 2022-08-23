#pragma once
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/shader.hpp>

#include "physics.hpp"

namespace QE {

struct Box {
    GL::Shader shader;
    Physics physics;
    GL::VAO vao;
    GL::VBO vbo;
    glm::vec3 color;

    Box();

    void update();
};

};