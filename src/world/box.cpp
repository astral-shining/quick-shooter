#include "box.hpp"
#include <models/box.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>

using namespace QE;

static const char* vs {
R"(#version 300 es
precision mediump float;
uniform float u_time;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

in vec3 a_pos;
out vec3 frag_pos;

void main() {
    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.);
})"
};

static const char* fs {
R"(#version 300 es
precision mediump float;

in vec3 frag_pos;

out vec4 frag_color;

uniform float u_time;
uniform vec3 u_color;

void main() {
	frag_color = vec4(
		u_color,
		1.
	);
}
)"
};

Box::Box() 
: shader(vs, fs), 
  physics(box_model),
  vbo(box_model) {
    shader.setAttribute({"a_pos"}, vbo);
}

void Box::update() {
    shader.use();
    vao.use();
    physics.update();
    shader.uniform("u_model", physics.transform.model);
    shader.uniform("u_color", color);
    glDrawArrays(GL_TRIANGLES, 0, box_model.size()*3);
}
