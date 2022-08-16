#include "input.hpp"
#include <emscripten/html5.h>
#include <cstdio>

using namespace QE;

Input::Input() {
    std::printf("%s\n", __PRETTY_FUNCTION__);
    const char* dom_target = "body";

    auto kcallback = [] (int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) -> EM_BOOL {
        static_cast<Input*>(userData)->onKeyCallback(eventType, keyEvent);
        return true;
    };

    auto mcallback = [] (int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) -> EM_BOOL {
        static_cast<Input*>(userData)->onMouseCallback(eventType, mouseEvent);
        return true;
    };

    emscripten_set_keydown_callback(dom_target, this, true, kcallback);
    emscripten_set_keypress_callback(dom_target, this, true, kcallback);
    emscripten_set_keyup_callback(dom_target, this, true, kcallback);
    emscripten_set_mousemove_callback(dom_target, this, true, mcallback);
}

void Input::update() {
    mouseMovement = {0, 0};
}

void Input::onKeyCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent) {
    auto& k = keys[keyEvent->keyCode];
    int e = (eventType -3) * -1;
    if (e == 1 && k <= 1) {
        k++;
    } else if (e == 0) {
        k = 0;
    }
}

bool Input::getKey(uint16_t key) {
    return keys[key] > 0;
}

bool Input::getKeyDown(uint16_t key) {
    return keys[key] == 1;
}

void Input::onMouseCallback(int eventType, const EmscriptenMouseEvent *mouseEvent) {
    mouseMovement = {mouseEvent->movementX, mouseEvent->movementY};
}


std::unique_ptr<Input> QE::input;
