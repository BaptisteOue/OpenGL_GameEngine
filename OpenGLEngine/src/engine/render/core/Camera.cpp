#include "Camera.h"
#include "Window.h"

#pragma region Public API

Camera::Camera()
	: m_Position(0, 1, -5), m_Front(0, 0, -1), m_Up(0, 1, 0)
{
}


Camera::~Camera()
{
}

void Camera::Init()
{
	m_LastX = ((float) Window::s_Width) / 2;
	m_LastY = ((float) Window::s_Height) / 2;

	m_CurrentX = m_LastX;
	m_CurrentY = m_LastY;

	m_Yaw = -90.0f;
	m_Pitch = 0.0f;
}

void Camera::Update(const glm::vec3& dCamera)
{
	float deltaX = (m_CurrentX - m_LastX) * s_Sensitivity;
	float deltaY = -(m_CurrentY - m_LastY) * s_Sensitivity;

	m_LastX = m_CurrentX;
	m_LastY = m_CurrentY;

	
	m_Yaw += deltaX;
	m_Pitch += deltaY;

	if (m_Pitch > 89.99f)
	{
		m_Pitch = 89.99f;
	}
	else if (m_Pitch < -89.99f)
	{
		m_Pitch = -89.99f;
	}

	m_Front.x = (float)(glm::cos(glm::radians(m_Pitch)) * glm::cos(glm::radians(m_Yaw)));
	m_Front.y = (float)(glm::sin(glm::radians(m_Pitch)));
	m_Front.z = (float)(glm::cos(glm::radians(m_Pitch)) * glm::sin(glm::radians(m_Yaw)));

	m_Front = glm::normalize(m_Front);

	Move(dCamera);
}

void Camera::SetCurrentMouseX(float currentX)
{
	m_CurrentX = currentX;
}

void Camera::SetCurrentMouseY(float currentY)
{
	m_CurrentY = currentY;
}

#pragma endregion


#pragma region Private API

void Camera::Move(const glm::uvec3& dCamera)
{
	glm::vec3 moveZ(0, 0, 0);
	glm::vec3 moveX(0, 0, 0);
	glm::vec3 moveY(0, 0, 0);

	glm::vec3 move(0, 0, 0);

	if (dCamera.z == -1) {
		moveZ += m_Front;
	}
	else if (dCamera.z == 1) {
		moveZ -= m_Front;
	}

	if (dCamera.x == 1) {
		moveX = glm::cross(m_Front, m_Up);
	}
	else if (dCamera.x == -1) {
		moveX = glm::cross(m_Up, m_Front);
	}

	if (dCamera.y == 1) {
		moveY += m_Up;
	}
	else if (dCamera.y == -1) {
		moveY -= m_Up;
	}

	move += moveX + moveZ + moveY;

	if (move.length() != 0) {
		glm::normalize(move);
		move *= Camera::s_Speed;
	}

	m_Position += move;
}

const glm::vec3 Camera::GetPos() const
{
	return m_Position;
}

glm::vec3 Camera::GetPos()
{
	return m_Position;
}

const glm::vec3 Camera::GetFront() const
{
	return m_Front;
}

const glm::vec3 Camera::GetUp() const
{
	return m_Up;
}

#pragma endregion
