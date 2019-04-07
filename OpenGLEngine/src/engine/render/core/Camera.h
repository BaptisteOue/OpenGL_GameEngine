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
	static constexpr auto s_Sensitivity = 0.3f;
	static constexpr auto s_Speed = 0.5f;

private:
	void Move(const glm::uvec3& dCamera);

public:
	Camera();
	~Camera();

	void Init();
	void Update(const glm::vec3& dCamera);

	const glm::vec3 GetPos() const;
	glm::vec3 GetPos();

	const glm::vec3 GetFront() const;
	const glm::vec3 GetUp() const;

	void SetCurrentMouseX(float currentX);
	void SetCurrentMouseY(float currentY);
};

