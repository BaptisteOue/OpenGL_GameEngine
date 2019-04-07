#pragma once

#include <glm/glm.hpp>
#include "../core/Camera.h"
#include "../lights/DirectionalLight.h"

class Transformations
{
public:
    Transformations() = delete;
    ~Transformations() { }

    static glm::mat4 GetProjectionMatrix(float fov, float nearPlane, float farPlane);
    static glm::mat4 GetModelMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
    static glm::mat4 GetViewMatrix(const Camera& camera);

	static glm::mat4 GetLightSpaceMatrix(const DirectionalLight& light, float nearPlane, float farPlane);
};