#pragma once
#include "camera.hpp"
#include "player.hpp"
#include <gl/shader.hpp>

namespace QE {

struct World {
    World();
    Camera camera;
    Player player;
    void update();
    void updateUniforms(GL::Shader& s);
};

inline World* current_world;

};