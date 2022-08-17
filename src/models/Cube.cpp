#include "Cube.hpp"

std::initializer_list<float> Cube_verts { 
     1.000000f,-1.000000f,-1.000000f,
     1.000000f,-1.000000f, 1.000000f,
    -1.000000f,-1.000000f, 1.000000f,
    -1.000000f,-1.000000f,-1.000000f,
     1.000000f, 1.000000f,-0.999999f,
     0.999999f, 1.000000f, 1.000001f,
    -1.000000f, 1.000000f, 1.000000f,
    -1.000000f, 1.000000f,-1.000000f,
};

std::initializer_list<uint32_t> Cube_faces { 
    1, 2, 3,
    7, 6, 5,
    4, 5, 1,
    5, 6, 2,
    2, 6, 7,
    0, 3, 7,
    0, 1, 3,
    4, 7, 5,
    0, 4, 1,
    1, 5, 2,
    3, 2, 7,
    4, 0, 7,
};
