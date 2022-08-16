#include "triangle.hpp"
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>
#include <time.hpp>

#include "transform.hpp"

using namespace QE;

static const char* vs {
R"(#version 300 es
precision mediump float;
uniform float u_time;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
in vec2 a_pos;
in vec2 a_degree;
out vec2 degree;

void main() {
   degree = a_degree;
   gl_Position = u_proj * u_view * u_model * vec4(a_pos, 0., 1.);
})"
};

static const char* fs {
R"(#version 300 es
precision mediump float;

in vec2 degree;
out vec4 FragColor;
uniform float u_time;
void main() {
    float t = u_time;
    FragColor = vec4(
        mod(degree.x*t, 1.),
        mod(degree.y*t, 1.),
        0.5,
        1.
    );
})"
};

Triangle::Triangle() : 
    shader(vs, fs),
    vbo({
        -0.5f, -0.5f, 0.f, 0.f,
        0.5f, -0.5f,  1.f, 0.f,
        0.5f, 0.5f,   1.f, 1.f,
        -0.5f, 0.5f,  0.f, 1.f
    }) {
    shader.setAttribute({"a_pos", "a_degree"}, vbo);
}
    
void Triangle::update() {
    //transform.rotation.y += 100 * time->delta;
    shader.use();
    vao.use();
    transform.update();
    shader.uniform("u_model", transform.model);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


