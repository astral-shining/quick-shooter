#pragma once
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <world/world.hpp>
#include <glm/gtx/string_cast.hpp>

#include "transform.hpp"

namespace QE {

struct Triangle {
    Transform transform;
    GL::Shader shader {
    R"(#version 300 es
    precision mediump float;
    uniform float u_time;
    uniform mat4 u_MVP;
    in vec2 aPos;
    void main() {
       gl_Position = u_MVP * vec4(aPos, 0.f, 1.f);
    })",
    R"(#version 300 es
    precision mediump float;
    out vec4 FragColor;
    uniform float u_time;
    void main() {
        FragColor = vec4(cos(gl_FragCoord.x / 10.f)/2.f + 0.5f, sin(gl_FragCoord.y/10.f)/2.f+0.5, 1.0f, 1.0f);
    })"
    };
    GL::VAO vao;
    GL::VBO vbo {
        {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        }
    };
    Triangle() {
        shader.setAttribute({"aPos"}, vbo);
    }
    
    void render() {
        shader.use();
        vao.use();
        glm::mat4 mvp = current_world->camera.getMatrix() * transform.getMatrix();
        shader.uniform("u_MVP", mvp);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
};

};
