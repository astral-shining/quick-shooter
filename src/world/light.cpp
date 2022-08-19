#include "light.hpp"

using namespace QE;

Light::Light() : intensity(1.f) { 
    transform.position = {0.f, 50.f, 0.f};
}
