#include "Transformations.h"
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../core/Window.h"
#include "../core/Camera.h"

#pragma region Public API

glm::mat4 Transformations::GetProjectionMatrix(float fov, float nearPlane, float farPlane)
{
    auto aspect = (float)Window::s_Width / (float)Window::s_Height;
	auto projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    return projectionMatrix;
}

glm::mat4 Transformations::GetModelMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto modelMatrix = glm::translate(glm::mat4(1), translation);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, scale);

    return modelMatrix;    
}

glm::mat4 Transformations::GetViewMatrix(const Camera& camera)
{
	auto target = camera.GetPos() + camera.GetFront();
	auto viewMatrix = glm::lookAt(camera.GetPos(), target, camera.GetUp());
	return viewMatrix;
}

#pragma endregion
