#pragma once

#include <glm/glm.hpp>

class Camera
{	

private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;

	float m_Pitch;
	float m_Yaw;

	float m_LastX;
	float m_LastY;
	float m_CurrentX;
	float m_CurrentY;

public:
	static float s_Sensitivity;
	static float s_Speed;

private:
	void Move(const glm::uvec3& dCamera);

public:
	Camera();
	~Camera();

	void Init();
	void Update(const glm::vec3& dCamera);
	void SetCurrentMouseX(float currentX);
	void SetCurrentMouseY(float currentY);
	glm::vec3 GetPos() const;
	glm::vec3 GetFront() const;
	glm::vec3 GetUp() const;
};

