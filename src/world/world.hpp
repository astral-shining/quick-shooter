#pragma once
#include "camera.hpp"
#include "player.hpp"
#include "light.hpp"
#include "map.hpp"

#include <gl/shader.hpp>
#include <memory>

namespace QE {

struct World {
    Camera camera;
    Light light;
    Map map;
    Player player;

    World();
    void update();
    void updateUniforms(GL::Shader& s);
};

extern std::unique_ptr<World> world;
};
