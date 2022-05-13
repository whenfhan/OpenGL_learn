#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), float Yaw = -90.0f, float Pitch = 0);
	glm::mat4 GetVierMatrix() { return glm::lookAt(pos, pos + front, up); }
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouse(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessScroll(float yoffset);

private:
	void updateCameraVectors();

public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	float yaw;
	float pitch;
	float moveSpeed;
	float mouseSensitivity;
	float zoom;
};

