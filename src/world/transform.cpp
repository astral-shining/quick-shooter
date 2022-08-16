#include "transform.hpp"
#include <glm/gtx/string_cast.hpp>

using namespace QE;

inline static void clampRotation(float& f) {
    f -= 360 * (int)(f/180);
}

Transform::operator glm::mat4() const {
    return model;
}

void Transform::update() {
    model = glm::mat4 { 1.f };
    model = glm::translate(model, position);

    clampRotation(rotation.x);
    clampRotation(rotation.y);
    clampRotation(rotation.z);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    model = glm::scale(model, scale);
}

