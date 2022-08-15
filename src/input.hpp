#pragma once
#include <array>
#include <cstdint>
#include <glm/vec2.hpp>
#include <memory>

struct EmscriptenKeyboardEvent;
struct EmscriptenMouseEvent;

namespace QE {

struct Input {
    std::array<uint8_t, 512> keys;
    glm::ivec2 mouseMovement;

    Input();

    bool getKey(uint16_t key);
    bool getKeyDown(uint16_t key);
    void update();
private:
    void onKeyCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent);
    void onMouseCallback(int eventType, const EmscriptenMouseEvent *mouseEvent);
};

extern std::unique_ptr<Input> input;

enum Keys {
    SPACE = 32,
    APOSTROPHE = 192, /* ' */
    COMMA = 188, /* , */
    MINUS = 222, /* - */
    PERIOD = 60, /* . */
    SLASH = 173, /* / */
    CONTROL = 17,
    N0 = 48,
    N1,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    SEMICOLON = 59, /* ; */
    EQUAL = 187, /* = */
    A = 65,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LEFT_BRACKET = 219, /* [ */
    BACKSLASH, /*, \ */
    RIGHT_BRACKET = 93, /* ] */
    GRAVE_ACCENT = 96, /* ` */
    WORLD_1 = 161, /* non-US #1 */
    WORLD_2, /*, non-US #2 */
    ESCAPE = 256,
    ENTER = 257,
    TAB = 258,
    BACKSPACE = 259,
    INSERT = 260,
    DELETE = 261,
    RIGHT = 262,
    LEFT = 37,
    DOWN = 40,
    UP = 38,
    PAGE_UP = 33,
    PAGE_DOWN = 34,
    HOME = 36,
    END = 35,
    CAPS_LOCK = 20,
    SCROLL_LOCK = 281,
    NUM_LOCK = 282,
    PRINT_SCREEN = 283,
    PAUSE = 284,
    F1 = 112,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25
/*  = KEY_KP_0 320
#define KEY_KP_1 321
#define KEY_KP_2 322
#define KEY_KP_3 323
#define KEY_KP_4 324
#define KEY_KP_5 325
#define KEY_KP_6 326
#define KEY_KP_7 327
#define KEY_KP_8 328
#define KEY_KP_9 329
#define KEY_KP_DECIMAL 330
#define KEY_KP_DIVIDE 331
#define KEY_KP_MULTIPLY 332
#define KEY_KP_SUBTRACT 333
#define KEY_KP_ADD 334
#define KEY_KP_ENTER 335
#define KEY_KP_EQUAL 336
#define KEY_LEFT_SHIFT 340

#define KEY_LEFT_ALT 342
#define KEY_LEFT_SUPER 343
#define KEY_RIGHT_SHIFT 344
#define KEY_RIGHT_CONTROL 345
#define KEY_RIGHT_ALT 346
#define KEY_RIGHT_SUPER 347
#define KEY_MENU 348
#define MOUSE_RIGHT 348
#define MOUSE_LEFT 349
#define KEY_LAST KEY_MENU
*/
};


};
