#include "InputManager.h"

InputManager::InputManager(ConfigUtil& _configUtil) : configUtil(_configUtil)
{
}

void InputManager::BindWindow(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		auto& self = *static_cast<InputManager*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			std::map<int, std::vector<std::function<void()>>> allActions = self.GetKeyPresses();

			for (auto& callback : allActions[key])
			{
				callback();
			}
		}
		else if (action == GLFW_RELEASE)
		{
			std::map<int, std::vector<std::function<void()>>> allActions = self.GetKeyReleases();

			for (auto& callback : allActions[key])
			{
				callback();
			}
		}
	});
}

void InputManager::RegisterKeyPress(KeyBinding keyBinding, std::function<void()> callback)
{
	int key = configUtil.GetKeyBinding(keyBinding);
	keyPresses[key].push_back(callback);
}

void InputManager::RegisterKeyRelease(KeyBinding keyBinding, std::function<void()> callback)
{
	int key = configUtil.GetKeyBinding(keyBinding);
	keyReleases[key].push_back(callback);
}

std::map<int, std::vector<std::function<void()>>> InputManager::GetKeyPresses()
{
	return keyPresses;
}

std::map<int, std::vector<std::function<void()>>> InputManager::GetKeyReleases()
{
	return keyReleases;
}