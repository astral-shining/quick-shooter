#pragma once 
#include <string>
#include <glm/vec2.hpp>

namespace QE {

struct Window {
    std::string title;
    glm::uvec2 size;
    const char* idcanvas {"#quick-canvas"};
    Window(std::string title="title");
    void setTitle(std::string title);
    void onResize(int w, int h);
    void lockPointer();
    void enableFullScreen();

    /*Window(std::string title, glm::uvec2 size = {640, 480});
    void setSize(int w, int h);
    void setPos(int w, int h);
    void onResize(int w, int h);
    GLFWwindow* getGlfwWindowPtr() const;
    void toggleFullScreen();
    ~Window();*/
};

extern Window window;

};