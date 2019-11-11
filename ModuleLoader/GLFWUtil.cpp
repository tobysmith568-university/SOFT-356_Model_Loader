#include "GLFWUtil.h"
#include "GLFW/glfw3.h"

using namespace std;

GLFWUtil::GLFWUtil(ConfigUtil& _configUtil, InputManager& _inputManager) : configUtil(_configUtil), inputManager(_inputManager)
{
}

void GLFWUtil::Init()
{
	glfwInit();

	int windowWidth = configUtil.GetInt(IntSetting::WindowWidth);
	int windowHeight = configUtil.GetInt(IntSetting::WindowHeight);
	string windowTitle = configUtil.GetString(StringSetting::WindowTitle);

	if (configUtil.GetBool(BoolSetting::FullScreenOnStartup))
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		window = glfwCreateWindow(mode->width, mode->height, &windowTitle[0], monitor, NULL);
	}
	else
	{
		window = glfwCreateWindow(windowWidth, windowHeight, &windowTitle[0], NULL, NULL);
	}

	glfwMakeContextCurrent(window);

	inputManager.BindWindow(window);
	inputManager.RegisterKeyPress(KeyBinding::Quit, [&]() { SetShouldClose(true); });
}

void GLFWUtil::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void GLFWUtil::WireFrameOnly()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

bool GLFWUtil::GetShouldClose()
{
	return glfwWindowShouldClose(window);
}

void GLFWUtil::SetShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}

void GLFWUtil::Exit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}