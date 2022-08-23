#pragma once
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/ebo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>
#include <time.hpp>
#include <models/model.hpp>

#include "physics.hpp"
#include "transform.hpp"

namespace QE {

struct Map {
    Physics physics;
    GL::Shader shader;
    GL::VAO vao;
    GL::VBO vbo;
    Transform transform;
    Map(Model& map_data);
    void update();

};

};
