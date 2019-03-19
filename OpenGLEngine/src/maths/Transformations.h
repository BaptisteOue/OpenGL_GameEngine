#pragma once

#include <glm/glm.hpp>
#include "../coreEngine/Camera.h"

class Transformations
{
public:
    Transformations() = delete;
    ~Transformations() { }

    static glm::mat4 GetProjectionMatrix(float fov, float nearPlane, float farPlane);
    static glm::mat4 GetModelMatrix(glm::vec3& translation, glm::vec3& rotation, float scale);
    static glm::mat4 GetViewMatrix(Camera& camera);
};