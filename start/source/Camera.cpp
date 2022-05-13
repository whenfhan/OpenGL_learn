#include "Camera.h"

Camera::Camera(glm::vec3 Position, glm::vec3 Up, float Yaw, float Pitch) :
	pos(Position),
	worldUp(Up),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	yaw(Yaw),
	pitch(Pitch),
	moveSpeed(2.5f),
	mouseSensitivity(0.1f),
	zoom(45.0f)
{
	updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = moveSpeed * deltaTime;
	switch (direction) {
	case Camera_Movement::FORWARD:
		pos += front * velocity;
		break;
	case Camera_Movement::BACKWARD:
		pos -= front * velocity;
		break;
	case Camera_Movement::LEFT:
		pos -= right * velocity;
		break;
	case Camera_Movement::RIGHT:
		pos += right * velocity;
		break;
	}
}

void Camera::ProcessMouse(float xoffset, float yoffset, GLboolean constrainPitch)
{
	yaw += xoffset * mouseSensitivity;
	pitch += yoffset * mouseSensitivity;
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::ProcessScroll(float yoffset)
{
	zoom -= (float)yoffset;
	zoom = zoom < 1.0f ? 1.0f : zoom;
	zoom = zoom > 45.0f ? 45.0f : zoom;
}

void Camera::updateCameraVectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

