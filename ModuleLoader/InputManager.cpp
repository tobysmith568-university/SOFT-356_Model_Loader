#include "InputManager.h"

InputManager::InputManager(ConfigUtil& _configUtil) : configUtil(_configUtil)
{
}

void InputManager::BindWindow(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		if (action == 0)
		{
			return;
		}

		auto& self = *static_cast<InputManager*>(glfwGetWindowUserPointer(window));

		std::map<int, std::vector<std::function<void()>>> allActions = self.GetActions();

		for (auto& callback : allActions[key])
		{
			callback();
		}
	});
}

void InputManager::RegisterMapping(KeyBinding keyBinding, std::function<void()> callback)
{
	int key = configUtil.GetKeyBinding(keyBinding);
	actions[key].push_back(callback);
}

std::map<int, std::vector<std::function<void()>>> InputManager::GetActions()
{
	return actions;
}