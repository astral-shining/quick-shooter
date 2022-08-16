#pragma once
#include "camera.hpp"
#include "player.hpp"
#include "triangle.hpp"

#include <gl/shader.hpp>
#include <memory>

namespace QE {

struct World {
    World();
    Camera camera;
    Player player;
    Triangle triangle;
    void update();
    void updateUniforms(GL::Shader& s);
};

extern std::unique_ptr<World> world;
};
