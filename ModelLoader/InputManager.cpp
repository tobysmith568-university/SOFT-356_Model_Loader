#include "InputManager.h"

InputManager::InputManager(ConfigUtil& _configUtil) : configUtil(_configUtil)
{
}

// Binds the window which keypresses should interect with
void InputManager::BindWindow(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);// Sets 'this' as the user pointer to be retrieved in the callback
	glfwSetKeyCallback(window, [](GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		auto& self = *static_cast<InputManager*>(glfwGetWindowUserPointer(window));// Retrive 'this'

		if (action == GLFW_PRESS || action == GLFW_REPEAT)// If the button is down
		{
			std::map<int, std::vector<std::function<void()>>> allActions = self.GetKeyRepeats();

			for (auto& callback : allActions[key])// For every callback for the current key being pressed
			{
				callback();// Run that callback
			}
		}

		if (action == GLFW_PRESS)// If the button was pressed down exactly in this game tick
		{
			std::map<int, std::vector<std::function<void()>>> allActions = self.GetKeyPresses();

			for (auto& callback : allActions[key])// For every callback for the current key being pressed
			{
				callback();// Run that callback
			}
		}
		
		if (action == GLFW_RELEASE)// If the button was released exactly in this game tick
		{
			std::map<int, std::vector<std::function<void()>>> allActions = self.GetKeyReleases();

			for (auto& callback : allActions[key])// For every callback for the current key being pressed
			{
				callback();// Run that callback
			}
		}
	});
}

// Registers a new callback function for when a key is pressed in the current game tick
void InputManager::RegisterKeyPress(KeyBinding keyBinding, std::function<void()> callback)
{
	int key = configUtil.GetKeyBinding(keyBinding);
	keyPresses[key].push_back(callback);
}

// Registers a new callback function for when a key is pressed in the current game tick or it continues to be pressed
void InputManager::RegisterKeyRepeat(KeyBinding keyBinding, std::function<void()> callback)
{
	int key = configUtil.GetKeyBinding(keyBinding);
	keyRepeats[key].push_back(callback);
}

// Registers a new callback function for when a key is released in the current game tick
void InputManager::RegisterKeyRelease(KeyBinding keyBinding, std::function<void()> callback)
{
	int key = configUtil.GetKeyBinding(keyBinding);
	keyReleases[key].push_back(callback);
}

std::map<int, std::vector<std::function<void()>>> InputManager::GetKeyPresses()
{
	return keyPresses;
}

std::map<int, std::vector<std::function<void()>>> InputManager::GetKeyRepeats()
{
	return keyRepeats;
}

std::map<int, std::vector<std::function<void()>>> InputManager::GetKeyReleases()
{
	return keyReleases;
}