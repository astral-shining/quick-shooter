#include "triangle.hpp"
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>
#include <time.hpp>
#include <models/Cube.hpp>
#include <input.hpp>

#include "transform.hpp"

using namespace QE;

static const char* vs {
R"(#version 300 es
precision mediump float;
uniform float u_time;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
in vec3 a_pos;

void main() {
   gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.);
})"
};

static const char* fs {
R"(#version 300 es
precision mediump float;

//in vec2 degree;
out vec4 FragColor;
uniform float u_time;
void main() {
    float t = cos(u_time)*5.+5.;
    FragColor = vec4(
        1.,
        0.,
        0.5,
        1.
    );
})"
};

Triangle::Triangle() : 
    shader(vs, fs),
    vbo(Cube_verts), 
    ebo(Cube_faces) {
    shader.setAttribute({"a_pos"}, vbo);
}
    
void Triangle::update() {
    glEnable(GL_DEPTH_TEST);  
    //transform.rotation.y += 100 * time->delta;
    shader.use();
    vao.use();
    static int a {};
    if (input->getKeyDown(Keys::UP)) {
        a++;
    } else if (input->getKeyDown(Keys::DOWN)) {
        a--;
    }
    transform.update();
    shader.uniform("u_model", transform.model);
    ebo.use();
    glDrawElements(GL_TRIANGLES, a, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 16);
    glDisable(GL_DEPTH_TEST);
}


