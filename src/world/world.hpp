#pragma once
#include "camera.hpp"
#include "player.hpp"
#include "triangle.hpp"

#include <gl/shader.hpp>
#include <memory>

namespace QE {

struct World {
    Camera camera;
    Triangle triangle;
    Player player;

    World();
    void update();
    void updateUniforms(GL::Shader& s);
};

extern std::unique_ptr<World> world;
};
