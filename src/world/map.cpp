#include "map.hpp"
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>
#include <time.hpp>
#include <input.hpp>

#include "world.hpp"
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

out vec3 frag_pos;

void main() {
    frag_pos = a_pos+vec3(0., .5, 0.);
    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.);
})"
};

static const char* fs {
R"(#version 300 es
precision mediump float;

in vec3 frag_pos;

out vec4 frag_color;

uniform float u_time;

vec3 getPixel(in vec3 pos) {
	float n = 5.2f;
	float line_size = 0.3f;
	float r = n+line_size;
    float p = float(
        int(mod(pos.x, r)/n) | int(mod(pos.y, r)/n) | int(mod(pos.z, r)/n)
    );
    return vec3(
		0., 
		p,
		p
	);
}

vec3 sampleTextureWithFilter(in vec3 pos, in vec3 uvwX, in vec3 uvwY, in float detail) {
    int sx = 5; // 1 + int(clamp(detail*length(uvwX-pos), 0., 8.));
    int sy = 5; // 1 + int(clamp(detail*length(uvwY-pos), 0., 8.));

    vec3 no = vec3( 0.0f );

    for( int j=0; j < sy; j++ ) 
	for( int i=0; i < sx; i++) {
        vec2 st = vec2(float(i), float(j))/vec2(float(sx),float(sy));
        no += getPixel(pos + st.x * (uvwX-pos) + st.y*(uvwY-pos));
    }

    return no / float(sx*sy);
}

void main() {
	vec3 fp_der = dFdx(frag_pos);
	vec3 fp_abj = dFdy(frag_pos);
	float detail = 1024.;

	frag_color = vec4(
		sampleTextureWithFilter(frag_pos, frag_pos + fp_der, frag_pos + fp_abj, detail),
		//getPixel(frag_pos),
		1.
	);
}
)"
};

Map::Map(Model& model) : 
    physics(model),
    shader(vs, fs),
    vbo(model) {
    shader.setAttribute({"a_pos"}, vbo);


}
static float area(const Face& f) {
    return glm::length(glm::cross(f[1]-f[0], f[2]-f[0]))/2.f;
}

static bool isInArea(const Face& f, const glm::vec3& p) {
    float a1 = area({f[0], f[1], p});
    float a2 = area({f[0], f[2], p});
    float a3 = area({f[1], f[2], p});
    return std::abs((a1 + a2 + a3) - area({f[0], f[1], f[2]})) < 0.4f;
}

void Map::update() {
    shader.use();
    vao.use();
    transform.update();
    shader.uniform("u_model", transform.model);
    glDrawArrays(GL_TRIANGLES, 0, physics.collision.model.size()*3);

    for (const auto& face : physics.collision.model) {
        if (isInArea(face, world->player.physics.transform.position)) {
            std::printf("ñ\n");
        }
    }
}


