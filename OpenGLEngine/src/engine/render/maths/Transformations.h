#pragma once

#include <glm/glm.hpp>
#include "../core/Camera.h"

class Transformations
{
public:
    Transformations() = delete;
    ~Transformations() { }

    static glm::mat4 GetProjectionMatrix(float fov, float nearPlane, float farPlane);
    static glm::mat4 GetModelMatrix(const glm::vec3& translation, const glm::vec3& rotation, float scale);
    static glm::mat4 GetViewMatrix(const Camera& camera);
};