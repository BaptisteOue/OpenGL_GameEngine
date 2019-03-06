#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/glm.hpp>
#include "Transformations.h"
#include "../coreEngine/Window.h"
#include "../coreEngine/Camera.h"


glm::mat4 Transformations::GetProjectionMatrix(float fov, float nearPlane, float farPlane)
{
    float aspect = (float)Window::s_Width / (float)Window::s_Height;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    return projectionMatrix;
}

glm::mat4 Transformations::GetModelMatrix(glm::vec3& translation, glm::vec3& rotation, float scale)
{
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1), translation);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

    return modelMatrix;    
}

glm::mat4 Transformations::GetViewMatrix(Camera& camera)
{
	glm::vec3 target = camera.GetPos() + camera.GetFront();
	glm::mat4 viewMatrix = glm::lookAt(camera.GetPos(), target, camera.GetUp());
	return viewMatrix;
}
