#include <emscripten/html5.h>
#include <assert.h>
#include <cstdio>
#include <world/world.hpp>
#include <time.hpp>
#include <input.hpp>
#include <window.hpp>

template<typename... Ts>
void updater(Ts&... args) {
    (args->update(), ...);
}

void main_loop() {
    updater(
        QE::time, 
        QE::world, 
        QE::input
    );
}

template<typename... Ts>
void init_uniques(std::unique_ptr<Ts>&... args) {
    (args.operator=(std::make_unique<Ts>()), ...);
}

int main() {
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.antialias = false;
    attrs.alpha = false;
	
    attrs.premultipliedAlpha = false;
    attrs.preserveDrawingBuffer = false;
    attrs.enableExtensionsByDefault = false;
    attrs.powerPreference = EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
    //attrs.failIfMajorPerformanceCaveat = true;
    attrs.majorVersion = 3;
    attrs.minorVersion = 0;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(idcanvas, &attrs);

    assert(ctx > 0);

    EMSCRIPTEN_RESULT r = emscripten_webgl_make_context_current(ctx);
    assert(r == EMSCRIPTEN_RESULT_SUCCESS);

    //emscripten_webgl_enable_OES_vertex_array_object(ctx);
    //emscripten_webgl_enable_WEBGL_draw_buffers(ctx);
    //emscripten_webgl_enable_WEBGL_multi_draw(ctx);
    //emscripten_webgl_enable_ANGLE_instanced_arrays(ctx);

    // std::printf("OpenGL version supported by this platform : %s\n", glGetString(GL_VERSION));
    
    init_uniques(QE::time, QE::window, QE::input, QE::world);

    emscripten_set_main_loop(main_loop, 0, false);
    return 0;
}
