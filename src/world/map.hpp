#pragma once
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/ebo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>
#include <time.hpp>
#include <models/model.hpp>

#include "transform.hpp"

namespace QE {

struct Map {
    Model& model;
    Transform transform;
    GL::Shader shader;
    GL::VAO vao;
    GL::VBO vbo;
    Map(Model& map_data);
    void update();

};

};
