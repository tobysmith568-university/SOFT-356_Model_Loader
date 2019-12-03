#include "GLFWUtil.h"
#include "GLFW/glfw3.h"

using namespace std;

GLFWUtil::GLFWUtil(ConfigUtil& _configUtil, InputManager& _inputManager) : configUtil(_configUtil), inputManager(_inputManager)
{
}

// Inits GLFW and the window
void GLFWUtil::Init()
{
	glfwInit();

	int windowWidth = configUtil.GetInt(IntSetting::WindowWidth);// Gets config
	int windowHeight = configUtil.GetInt(IntSetting::WindowHeight);
	string windowTitle = configUtil.GetString(StringSetting::WindowTitle);

	if (configUtil.GetBool(BoolSetting::FullScreenOnStartup))
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();// Creates a fullscreen window
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		window = glfwCreateWindow(mode->width, mode->height, &windowTitle[0], monitor, NULL);
	}
	else
	{
		window = glfwCreateWindow(windowWidth, windowHeight, &windowTitle[0], NULL, NULL);// Creates a windowed window
	}

	glfwMakeContextCurrent(window);

	inputManager.BindWindow(window);// Set the window as the current window in the input manager
	inputManager.RegisterKeyPress(KeyBinding::Quit, [&]()
	{
		SetShouldClose(true);
	});// Create a keybinding for closing the window
}

// To be run every game tick
void GLFWUtil::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// Returns if the window has been told to close or not
bool GLFWUtil::GetShouldClose()
{
	return glfwWindowShouldClose(window);
}

// Tells the window that it should or shouldn't close
void GLFWUtil::SetShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}

// Frees resources
void GLFWUtil::Exit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}