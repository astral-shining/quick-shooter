#include "window.hpp"
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

using namespace QE;

Window::Window(std::string title) {
    std::printf("%s\n", __PRETTY_FUNCTION__);
    setTitle(std::move(title));
    double width, height;
    emscripten_get_element_css_size("html", &width, &height);
    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, [] (int, const EmscriptenUiEvent *uiEvent, void *userData) -> EM_BOOL {
		static_cast<Window*>(userData)->onResize(uiEvent->windowInnerWidth, uiEvent->windowInnerHeight);
		return true;
	});
    emscripten_set_canvas_element_size(idcanvas, width, height);
    size.x = width;
    size.y = height;
    emscripten_set_dblclick_callback("body", this, true, [] (int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) -> EM_BOOL {
        static_cast<Window*>(userData)->enableFullScreen();
        return true;
    });

}

void Window::setTitle(std::string t) {
    title = std::move(t);
    emscripten_set_window_title(title.data());
}

void Window::onResize(int w, int h) {
    size.x = w;
    size.y = h;
    emscripten_set_canvas_element_size(idcanvas, w, h);
    glViewport(0, 0, w, h);
}

void Window::lockPointer() {
    emscripten_request_pointerlock("body", true);
}

void Window::enableFullScreen() {
    EM_ASM(
        document.body.requestFullscreen().then(() => {
            document.body.requestPointerLock();
        });
    );
}
Window QE::window;