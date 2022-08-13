#include <emscripten/html5.h>
#include <assert.h>
#include <cstdio>
#include <world/world.hpp>
#include <time.hpp>
#include <input.hpp>


void main_loop() {
    static QE::World world;
	QE::time.update();
	world.update();
	QE::input.update();
}

int main() {
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
	attrs.majorVersion = 3;
	attrs.minorVersion = 0;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(QE::window.idcanvas, &attrs);

	assert(ctx > 0);

	EMSCRIPTEN_RESULT r = emscripten_webgl_make_context_current(ctx);
	assert(r == EMSCRIPTEN_RESULT_SUCCESS);

	//emscripten_webgl_enable_OES_vertex_array_object(ctx);
	//emscripten_webgl_enable_WEBGL_draw_buffers(ctx);
	//emscripten_webgl_enable_WEBGL_multi_draw(ctx);
	//emscripten_webgl_enable_ANGLE_instanced_arrays(ctx);

    // std::printf("OpenGL version supported by this platform : %s\n", glGetString(GL_VERSION));
	

	emscripten_set_main_loop(main_loop, 0, false);
    return 0;
}
