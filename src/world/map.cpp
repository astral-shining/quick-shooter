#include "map.hpp"
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/shader.hpp>
#include <GLES3/gl3.h>
#include <glm/gtx/string_cast.hpp>
#include <time.hpp>
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
in vec2 a_tex_coord;

out vec3 frag_pos;

void main() {
    frag_pos = vec3(u_model * vec4(a_pos + vec3(0.0, 5.f, 0.0), 1.));
    gl_Position = u_proj * u_view * vec4(a_pos, 1.);
})"
};

static const char* fs {
R"(#version 300 es
precision mediump float;

in vec2 tex_coord;
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
		p * 0.5
	);
}

vec3 sampleTextureWithFilter(in vec3 pos, in vec3 uvwX, in vec3 uvwY, in float detail) {
    int sx = 1 + int(clamp(detail*length(uvwX-pos), 0., 8.));
    int sy = 1 + int(clamp(detail*length(uvwY-pos), 0., 8.));

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
		1.
	);
}
)"
};

Map::Map(Model& model) : 
    model(model),
    shader(vs, fs),
    vbo(model.data) {
    shader.setAttribute({"a_pos", 5}, vbo);

}
    
void Map::update() {
    glEnable(GL_DEPTH_TEST);  
    shader.use();
    vao.use();
    //transform.rotation.y += 100.f * time->delta;
    transform.update();
    shader.uniform("u_model", transform.model);
    glDrawArrays(GL_TRIANGLES, 0, model.count);
    glDisable(GL_DEPTH_TEST);
}


