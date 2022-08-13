#include "transform.hpp"
#include <glm/gtx/string_cast.hpp>

using namespace QE;

static float clampRotation(float n) {
    return fmod(n, 180.f);
}

glm::mat4 Transform::getMatrix() {
    glm::mat4 m { 1.f };
    m = glm::translate(m, position);
    m = glm::rotate(m, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    //m = glm::rotate(m, glm::radians(clampRotation(rotation.z)), glm::vec3(0.0f, 0.0f, 1.0f));
    //m = glm::rotate(m, glm::radians(clampRotation(rotation.x)), glm::vec3(1.0f, 0.0f, 0.0f));
    
    m = glm::scale(m, scale);
    return m;
}
