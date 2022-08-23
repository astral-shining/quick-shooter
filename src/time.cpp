#include "time.hpp"
#include <emscripten/html5.h>

using namespace QE; 

EM_JS(void, update_fps, (int n), {
    //const fps = document.getElementById("fps");
    fps.innerHTML = "FPS: " + n;
});

void Time::update() {
    static uint32_t next_sec = 1;
    static double time_last_frame {};
    static uint32_t fps_count {};

    now = emscripten_get_now()/1000;
    delta = now-time_last_frame;
    time_last_frame = now;
	fps_count++;
    
	if (now >= next_sec) {
		next_sec = now+1;
        fps = fps_count;
        fps_count = 0;

        update_fps(fps);
	}
}

std::unique_ptr<Time> QE::time;
