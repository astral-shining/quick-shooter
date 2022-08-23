#pragma once
#include <initializer_list>
#include <cstdint>
#include <glm/vec3.hpp>
#include <array>

using Face = std::array<glm::vec3, 3>;
using Model = std::initializer_list<Face>;