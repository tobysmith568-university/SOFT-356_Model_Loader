#pragma once
#include "ConfigUtil.h"
#include <functional>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	InputManager(ConfigUtil& _configUtil);
	void BindWindow(GLFWwindow* window);
	void RegisterMapping(KeyBinding keyBinding, std::function<void()> callback);
	std::map<int, std::vector<std::function<void()>>> GetActions();

private:
	ConfigUtil& configUtil;
	std::map<int, std::vector<std::function<void()>>> actions;
};