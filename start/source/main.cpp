#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

float deltaTime = 0.0f; // ����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

bool firstMouse = true;
float lastX = 400, lastY = 300; // ��һ�����λ��
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


int main()
{
	// ��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback); // �����ص�
	glfwSetScrollCallback(window, scroll_callback); // �󶨹��ֻص�

	// ʹ��GLAD���ض�ӦOPENGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* ����OPENGLȫ��״̬ */
	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ��겻���Ƴ�ȥ

	// ������ɫ��
	Shader ourShader("shader_source/shader.vs", "shader_source/shader.fs");
	// ����ģ��
	Model ourModel("./resources/nanosuit/nanosuit.obj");
	
	/* ��Ⱦѭ�� */
	while (!glfwWindowShouldClose(window)) {
		// ��ǰ��Ⱦʱ��
		float currentFram = (float)glfwGetTime();
		deltaTime = currentFram - lastFrame;
		lastFrame = currentFram;

		// input
		processInput(window);

		// render
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		// ͸�Ӻ͹۲����
		glm::mat4 view = camera.GetVierMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)screenWidth / screenHeight, 0.1f, 100.0f);
		ourShader.setUniform("view", view);
		ourShader.setUniform("projection", projection);

		// ��������ת��
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	
		ourShader.setUniform("model", model);

		ourModel.Draw(ourShader);
		

		// check & swap
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ��������
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		firstMouse = false;
		lastX = (float)xpos;
		lastY = (float)ypos;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset = (float)(lastY - ypos);
	lastX = (float)xpos;
	lastY = (float)ypos;
	camera.ProcessMouse(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessScroll((float)yoffset);
}


